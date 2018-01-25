#!/usr/bin/env ruby
if __FILE__ == $PROGRAM_NAME
  Dir.mkdir('tmp') unless File.exist?('tmp')
  unless File.exist?("tmp/mruby")
    system("git clone -b stable --single-branch https://github.com/mruby/mruby.git tmp/mruby")
  end

  build_args = ARGV.join(' ')
  exit system(%Q[cd tmp/mruby && MRUBY_CONFIG=#{File.expand_path __FILE__} ruby minirake #{build_args}])
end

MRuby::Build.new do |conf|
  toolchain :gcc
  conf.enable_test
  conf.gem File.expand_path(File.dirname(__FILE__))
end
