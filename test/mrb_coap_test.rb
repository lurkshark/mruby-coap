assert('Coap.ping method exists') do
  assert_true(Coap.respond_to?(:ping), "Coap module is not responding to ::ping")
end

assert('Coap::Header class stores header info') do
  VERSION, TYPE, TOKEN_LENGTH, CODE, ID = 1, 2, 3, 4, 5
  target = Coap::Header.new(VERSION, TYPE, TOKEN_LENGTH, CODE, ID)
  assert_equal(target.version,      VERSION,      'Header#version is incorrect')
  assert_equal(target.type,         TYPE,         'Header#type is incorrect')
  assert_equal(target.token_length, TOKEN_LENGTH, 'Header#token_length is incorrect')
  assert_equal(target.code,         CODE,         'Header#code is incorrect')
  assert_equal(target.id,           ID,           'Header#id is incorrect')
  assert_true(target.respond_to?(:dump), "Header#dump is undefined")
  target.dump
end
