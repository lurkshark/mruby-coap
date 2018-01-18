#!/usr/bin/env ruby
if __FILE__ == $0
    repository, dir = 'https://github.com/mruby/mruby.git', 'tmp/mruby'
    Dir.mkdir('tmp') unless File.exist?('tmp')
    unless File.exist?(dir)
        system("git clone #{repository} #{dir}")
    end

    exit system(%Q[cd #{dir} && MRUBY_CONFIG=#{File.expand_path(__FILE__)} ruby minirake test])
end

MRuby::Build.new do |conf|
    toolchain :gcc
    conf.enable_test
    conf.gem File.expand_path(File.dirname(__FILE__))
end
