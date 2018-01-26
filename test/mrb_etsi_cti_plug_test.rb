# ETSI CTI Plugtests Guide First Draft V0.0.15 (2012-02)
# http://www.etsi.org/plugtests/coap/coap.htm
COAP_TEST_SERVER = 'coap.me'

assert('TD_COAP_CORE_01') do
  response = CoAP::Client.get(COAP_TEST_SERVER, 'test')
  # response.type
  # response.code
  # response.text
end
