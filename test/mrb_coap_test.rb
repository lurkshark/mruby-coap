assert('CoAP.ping method exists') do
  assert_true(CoAP.respond_to?(:ping), "CoAP module is not responding to ::ping")
end
