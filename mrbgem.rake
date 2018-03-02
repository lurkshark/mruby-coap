MRuby::Gem::Specification.new('mruby-coap') do |spec|
  spec.license = "MIT"
  spec.author  = "joel"
  spec.cc.flags << "-DWITH_POSIX"
  # Installing libcoap from source puts it in the local subdirectory.
  spec.cc.include_paths << "/usr/include/coap" << "/usr/local/include/coap"
  ENV['LD_LIBRARY_PATH'] = "/usr/lib:/usr/local/lib:#{ENV['LD_LIBRARY_PATH']}"
  spec.linker.library_paths << "/usr/lib" << "/usr/local/lib"
  spec.linker.libraries << "coap-1"
end
