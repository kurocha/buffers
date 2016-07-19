
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "1.0"

define_project "Buffers" do |project|
	project.add_author "Samuel Williams"
	project.license = "MIT License"

	project.version = "1.0.0"
end


define_target "buffers" do |target|
	target.build do |environment|
		source_root = target.package.path + 'source'
		
		copy headers: source_root.glob('Buffers/**/*.hpp')
		
		build static_library: "Buffers", source_files: source_root.glob('Buffers/**/*.cpp')
	end
	
	target.depends :platform
	target.depends "Language/C++11"
	
	target.depends "Build/Files"
	target.depends "Build/Clang"
	
	target.provides "Library/Buffers" do
		append linkflags {install_prefix + "lib/libBuffers.a"}
	end
end

define_target "buffers-tests" do |target|
	target.build do |environment|
		test_root = target.package.path + 'test'
		
		run tests: "Buffers", source_files: test_root.glob('Buffers/**/*.cpp')
	end
	
	target.depends "Library/UnitTest"
	target.depends "Library/Buffers"
	
	target.provides "Test/Buffers"
end

define_configuration "test" do |configuration|
	configuration[:source] = "http://github.com/kurocha/"
	
	configuration.require "platforms"
	configuration.require "build-files"
	
	configuration.require "unit-test"
	
	configuration.require "language-cpp-class"
end
