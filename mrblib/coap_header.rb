module Coap
  class Header

    attr_reader :version, :type, :token_length, :code, :id

    def initialize(version, type, token_length, code, id)
      @version = version
      @type = type
      @token_length = token_length
      @code = code
      @id = id
    end
  end
end
