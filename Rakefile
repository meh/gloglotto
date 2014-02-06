require 'rake'
require 'rake/clean'
require 'fileutils'

CXX     = ENV['CXX'] || 'clang++'
CFLAGS  = "-Wall -Wextra -pedantic -Werror-implicit-function-declaration -Wno-gnu-zero-variadic-macro-arguments -funroll-loops -std=c++11 -pipe -Iinclude #{ENV['CFLAGS']}"
LDFLAGS = "-lGL -lGLEW -lglut #{ENV['LDFLAGS']}"

SOURCES = FileList['source/**/*.cpp']
OBJECTS = SOURCES.ext('o')

EXAMPLES = FileList['examples/*.cpp']
TESTS    = FileList['tests/*.cpp']

CLEAN.include(OBJECTS.existing).include(EXAMPLES.ext('').existing).include(TESTS.ext('').existing)
CLOBBER.include('libgloglotto.so', 'libgloglotto-static.a')

task :default => ['libgloglotto.so', 'libgloglotto-static.a']

task :install, [:path] => ['libgloglotto.so', 'libgloglotto-static.a'] do |t, args|
	path = args[:path] || '/usr/local'

	FileUtils.install 'include/gloglotto', path
	FileUtils.install FileList['source/*.tpp'], "#{path}/include/gloglotto"
	FileUtils.install FileList['source/maths/*.tpp'], "#{path}/include/gloglotto/maths"
end

task :examples => 'libgloglotto-static.a' do
	EXAMPLES.each {|file|
		sh "#{CXX} #{CFLAGS} -o #{file.sub(/\.cpp/, '')} #{file} #{LDFLAGS} -L. -lgloglotto-static"
	}
end

task :doc do
	sh "cldoc #{CFLAGS} -- --output doc #{FileList['include/**/**'].exclude { |f| File.directory?(f) }} #{FileList['source/**/*.cpp']}"
end

task :test do
	TESTS.each {|file|
		sh "#{CXX} #{CFLAGS} -Itests/amirite -o #{file.sub(/\.cpp/, '')} #{file} #{LDFLAGS} -L. -lgloglotto-static"
		sh "./#{file.sub(/\.cpp/, '')}"
	}
end

file 'libgloglotto.so' => OBJECTS do
	sh "#{CXX} #{CFLAGS} -fPIC #{OBJECTS} -shared -Wl,-soname,libgloglotto -o libgloglotto.so #{LDFLAGS}"
end

file 'libgloglotto-static.a' => OBJECTS do
	sh "ar rcs libgloglotto-static.a #{OBJECTS}"
end

rule '.o' => '.cpp' do |t|
	sh "#{CXX} #{CFLAGS} -fPIC -o #{t.name} -c #{t.source}"
end
