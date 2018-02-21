# ETSI CTI Plugtests Guide First Draft V0.0.15 (2012-02)
# http://www.etsi.org/plugtests/coap/coap.htm
COAP_TEST_SERVER = "coap.me"

assert("TD_COAP_CORE_01") do
  response = CoAP::Client.get(COAP_TEST_SERVER, "test")
  assert_include response, "welcome to the ETSI plugtest!"
end

assert("TD_COAP_CORE_04") do
  response = CoAP::Client.delete(COAP_TEST_SERVER, "test")
  assert_equal "DELETE OK", response
end
