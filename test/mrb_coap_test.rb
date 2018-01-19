assert('Coap::ping exists') do
    assert_true(Coap.respond_to?(:ping), "Coap is not responding to ::ping")
end
