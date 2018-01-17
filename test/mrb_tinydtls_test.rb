assert('TinyDTLS::ping exists') do
    TinyDTLS.respond_to?(:ping) and false
end
