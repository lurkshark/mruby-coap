MRuby::Gem::Specification.new('mruby-coap') do |spec|
  spec.license = "MIT"
  spec.author  = "joel"
  spec.cc.flags << "-DWITH_POSIX"
  spec.cc.include_paths << "/usr/include/coap"
  ENV['LD_LIBRARY_PATH'] = "/usr/lib:#{ENV['LD_LIBRARY_PATH']}"
  spec.linker.library_paths << "/usr/lib"
  spec.linker.libraries << "coap-1"
end
