assert('TinyDTLS::ping exists') do
    assert_true(TinyDTLS.respond_to?(:ping), "TinyDTLS is not responding to ::ping")
end
