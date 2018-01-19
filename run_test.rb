#!/usr/bin/env ruby
if __FILE__ == $PROGRAM_NAME
  def git_clone(repository, dir, branch = 'master')
    Dir.mkdir('tmp') unless File.exist?('tmp')
    unless File.exist?("tmp/#{dir}")
      system("git clone -b #{branch} --single-branch #{repository} tmp/#{dir}")
    else true end
  end

  exit false unless git_clone('https://github.com/mruby/mruby.git', 'mruby', 'stable')
  exit false unless git_clone('https://github.com/RIOT-Makers/YaCoAP.git', 'yacoap')

  build_args = ARGV.join(' ')
  Dir.mkdir('src/yacoap') unless File.exist?('src/yacoap')
  exit false unless system(%Q[cp tmp/yacoap/*.c tmp/yacoap/*.h src/yacoap/])
  exit system(%Q[cd tmp/mruby && MRUBY_CONFIG=#{File.expand_path __FILE__} ruby minirake #{build_args}])
end

MRuby::Build.new do |conf|
  toolchain :gcc
  conf.enable_test
  conf.gem File.expand_path(File.dirname(__FILE__))
end
