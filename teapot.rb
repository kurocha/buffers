
#
#  This file is part of the "Teapot" project, and is released under the MIT license.
#

teapot_version "3.0"

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
	target.depends "Language/C++14"
	
	target.provides "Library/Buffers" do
		source_root = target.package.path + 'source'
		
		library_path = build static_library: "Buffers", source_files: source_root.glob('Buffers/**/*.cpp')
		
		append linkflags library_path
		append header_search_paths source_root
	end
end

define_target "buffers-tests" do |target|
	target.depends "Library/UnitTest"
	
	target.depends "Language/C++14"
	target.depends "Library/Buffers"
	
	target.provides "Test/Buffers" do |*arguments|
		test_root = target.package.path + 'test'
		
		run source_files: test_root.glob('Buffers/**/*.cpp'), arguments: arguments
	end
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
