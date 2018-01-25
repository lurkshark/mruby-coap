MRuby::Gem::Specification.new('mruby-coap') do |spec|
  spec.license = 'MIT'
  spec.author  = 'joel'
  spec.cc.flags << "-DWITH_POSIX"
  spec.cc.include_paths << "/usr/local/include/coap/"
  spec.linker.library_paths << "/usr/local/lib/"
  spec.linker.libraries << "coap-1"
end
