module CoAP
  class Client

    DEFAULT_PORT = 5683
    DEFAULT_TYPE = CON

    def self.get(host, path, options = {})
      port = options[:port] || DEFAULT_PORT
      type = options[:type] || DEFAULT_TYPE
      _send(GET, host, port, path, type, nil)
    end

    def self.post(host, path, payload, options = {})
      port = options[:port] || DEFAULT_PORT
      type = options[:type] || DEFAULT_TYPE
      _send(POST, host, port, path, type, payload.to_s)
    end

    def self.delete(host, path, options = {})
      port = options[:port] || DEFAULT_PORT
      type = options[:type] || DEFAULT_TYPE
      _send(DELETE, host, port, path, type, nil)
    end
  end
end
