module CoAP
  class Client

    def self.get(host, path, options = {})
      port = options[:port] || 5683
      type = options[:type] || :con
      send(:get, host, port, path, type)
    end
  end
end
