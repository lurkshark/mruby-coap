# mruby-coap
[![Build Status](https://travis-ci.com/lurkshark/mruby-coap.svg?branch=master)](https://travis-ci.com/lurkshark/mruby-coap)

## Installing

This package depends on [libcoap](https://libcoap.net/doc/install.html). There is a [Dockerfile](https://github.com/lurkshark/mruby-coap/blob/master/Dockerfile) included that can be used for building and running the tests as well.

```bash
git clone https://github.com/lurkshark/mruby-coap.git
cd mruby-coap && ruby run_test.rb test
```

## Usage
Currently this package only supports a basic GET/POST/PUT/DELETE client. Future improvements should include a more advanced client as well as a server implementation.

### CoAP::Client
The client currently only has class methods which basically follow the same pattern as the [Net::HTTP](https://ruby-doc.org/stdlib/libdoc/net/http/rdoc/Net/HTTP.html) shortcut methods.

#### Class Methods
-----
**`(String) get(host, path, options = { port: 5683, type: CON })`**

Makes a synchronous GET request to the given server/path and returns the payload of the response as a string.

```ruby
response = CoAP::Client.get("coap.me", "test")
assert_include response, "welcome to the ETSI plugtest!"
```
-----
**`(String) post(host, path, payload, options = { port: 5683, type: CON })`**

Makes a synchronous POST request to the given server/path with the payload, and returns the payload of the response as a string.

```ruby
response = CoAP::Client.post("coap.me", "test", "PAYLOAD")
assert_equal "POST OK", response
```
-----
**`(String) put(host, path, payload, options = { port: 5683, type: CON })`**

Makes a synchronous PUT request to the given server/path with the payload, and returns the payload of the response as a string.

```ruby
response = CoAP::Client.put("coap.me", "test", "PAYLOAD")
assert_equal "PUT OK", response
```
-----
**`(String) delete(host, path, options = { port: 5683, type: CON })`**

Makes a synchronous DELETE request to the given server/path, and returns the payload of the response as a string.

```ruby
response = CoAP::Client.delete("coap.me", "test")
assert_equal "DELETE OK", response
```
-----
*Issues and Pull Requests welcome.*
