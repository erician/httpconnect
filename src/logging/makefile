LOGGINGDIR := logging


$(OBJDIR)/httpc_config.o: $(LOGGINGDIR)/httpc_config.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/httpc_logging.o: $(LOGGINGDIR)/httpc_logging.cc $(LOGGINGDIR)/httpc_logging.ini ../logs
	$(CC) $(CFLAGS) -c -o $@ $<

../logs: 
	mkdir ../logs



