.PHONY: clean 
HTTPSPROXY = ../obj/httpc
PRODUCTS = $(HTTPSPROXY)
default: $(PRODUCTS)

OBJDIR = ../obj

include core/makefile
include utils/makefile
include utils/args/makefile
include logging/makefile

include unittest/makefile
include unittest/utils/makefile
include unittest/utils/args/makefile
include unittest/logging/makefile
include unittest/core/makefile

# OBJS can deal with either .cc or .c 
OBJS += $(OBJDIR)/httpc_handler.o $(OBJDIR)/httpc_proxy.o 
OBJS += $(OBJDIR)/httpc_http_response.o $(OBJDIR)/httpc_http_request.o
OBJS += $(OBJDIR)/httpc_config.o $(OBJDIR)/httpc_logging.o 
OBJS += $(OBJDIR)/httpc_stringutil.o
OBJS += $(OBJDIR)/httpc_options.o $(OBJDIR)/httpc_args.o $(OBJDIR)/httpc_option_error.o
OBJS += $(OBJDIR)/httpc_main.o

JUNK = *~ $(OBJDIR)/*.o $(OBJDIR)/*.a  

# Define the tools we are going to use
CC= g++
LD = g++

CFLAGS = -g -Wall -Wno-unused -Wno-sign-compare -std=c++11 -I.

LIBS = -lm -lc -lpthread

$(OBJDIR)/httpc_main.o: httpc_main.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(PRODUCTS): $(OBJS)
	$(LD) -o $@  $^  $(LIBS)
	cp $(PRODUCTS) ./

start: $(PRODUCTS)
	@nohup $(PRODUCTS) -i 115.156.135.252 -p 9001 &
	@netstat -lpn | grep "httpc" | grep "^tcp" 

stop: $(PRODUCTS)
	@for pid in `ps -ef | grep '../obj/httpc' | grep -v 'grep' | tr -s " " | cut -d " " -f 2`; do echo "kill "$${pid}; kill $${pid}; done


#unittest,using googletest:https://github.com/google/googletest/blob/master/googletest/docs/Primer.md
#this make no sense, and just test googletest

ut-utils-stringutil: $(OBJDIR)/httpc_stringutil_ut
	./$(OBJDIR)/httpc_stringutil_ut

ut-utils-args: $(OBJDIR)/httpc_args_ut
	./$(OBJDIR)/httpc_args_ut

ut-logging-logging: $(OBJDIR)/httpc_logging_ut 
	./$(OBJDIR)/httpc_logging_ut  

ut-logging-config: $(OBJDIR)/httpc_config_ut
	./$(OBJDIR)/httpc_config_ut

ut-core-http-response: $(OBJDIR)/httpc_http_response_ut
	./$(OBJDIR)/httpc_http_response_ut

ut-core-http-request: $(OBJDIR)/httpc_http_request_ut
	./$(OBJDIR)/httpc_http_request_ut

ut-core-handler: $(OBJDIR)/httpc_handler_ut
	./$(OBJDIR)/httpc_handler_ut

clean:
	@rm -f $(JUNK) $(PRODUCTS) ./httpc


