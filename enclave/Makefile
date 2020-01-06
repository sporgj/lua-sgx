include header.mk

CC ?= gcc

APP_PATH = ..

objs := \
	main.o

lua_lib = lua/liblua.a

build = \
        @if [ -z "$V" ]; then \
                echo '    [$1]  $@'; \
                $2; \
        else \
                echo '$2'; \
                $2; \
        fi



.PHONY: all
all: lua_enclave.signed.so

%.o: %.c
	$(call build,CC,$(CC) $(Enclave_C_Flags) -c $< -o $@)

$(lua_lib):
	make -C lua

private_key.pem:
	openssl genrsa -out $@ -3 3072

enclave_t.c: enclave.edl
	@$(SGX_EDGER8R) --trusted --trusted-dir . $^
	@echo "GEN +> $@"

enclave_t.o: enclave_t.c
	$(call build,CC,$(CC) $(Enclave_C_Flags) -c $< -o $@)


lua_enclave.so: enclave_t.o $(objs) $(lua_lib)
	$(call build,CC,$(CC) $^ -o $@ $(Enclave_Link_Flags))

lua_enclave.signed.so: lua_enclave.so private_key.pem config.xml
	@$(SGX_ENCLAVE_SIGNER) sign -key private_key.pem -enclave $< -out $@ -config config.xml
	@echo "SIGN => $@"

.PHONY: clean
clean:
	rm -rf *.so *.o enclave_t.*
