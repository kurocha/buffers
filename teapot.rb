
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "1.3"

# Project Metadata

define_project "buffers" do |project|
	project.title = 'Buffers'
	project.summary = 'Abstractions for managing blocks of data.'
	
	project.license = "MIT License"
	
	project.add_author 'Samuel Williams', email: 'samuel.williams@oriontransfer.co.nz'
	
	project.version = "1.0.0"
end

# Build Targets

define_target 'buffers-library' do |target|
	target.build do
		source_root = target.package.path + 'source'
		
		copy headers: source_root.glob('Buffers/**/*.hpp')
		
		build static_library: "Buffers", source_files: source_root.glob('Buffers/**/*.cpp')
	end
	
	target.depends 'Build/Files'
	target.depends 'Build/Clang'
	
	target.depends :platform
	target.depends "Language/C++11", private: true
	
	target.depends "Build/Files"
	target.depends "Build/Clang"
	
	target.provides "Library/Buffers" do
		append linkflags [
			->{install_prefix + 'lib/libBuffers.a'},
		]
	end
end

define_target "buffers-tests" do |target|
	target.build do |*arguments|
		test_root = target.package.path + 'test'
		
		run tests: "Buffers", source_files: test_root.glob('Buffers/**/*.cpp'), arguments: arguments
	end
	
	target.depends "Language/C++14", private: true
	
	target.depends "Library/UnitTest"
	target.depends "Library/Buffers"
	
	target.provides "Test/Buffers"
end

# Configurations

define_configuration "development" do |configuration|
	configuration[:source] = "https://github.com/kurocha"
	
	# Provides all the build related infrastructure:
	configuration.require "platforms"
	configuration.require "build-files"
	
	# Provides unit testing infrastructure and generators:
	configuration.require "unit-test"
	
	# Provides some useful C++ generators:
	configuration.require 'generate-project'
	configuration.require 'generate-travis'
	configuration.require "generate-cpp-class"
end

define_configuration "buffers" do |configuration|
	configuration.public!
end
