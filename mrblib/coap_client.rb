module CoAP
  class Client

    DEFAULT_PORT = 5683
    DEFAULT_TYPE = :con

    def self.get(host, path, options = {})
      port = options[:port] || DEFAULT_PORT
      type = options[:type] || DEFAULT_TYPE
      _send(:get, host, port, path, type)
    end
  end
end
