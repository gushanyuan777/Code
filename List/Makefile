LATEX=pdflatex  
TARGET=report  
PROGRAM=List  
  
all: $(PROGRAM)  
  
report: $(TARGET).pdf  
  
$(PROGRAM): List.c  
	gcc -o List List.c  
  
$(TARGET).pdf: $(TARGET).tex  
	$(LATEX) $<  
	$(LATEX) $<  
  
.PHONY: clean  
  
clean:  
	rm -f $(TARGET).pdf *.log *.aux $(PROGRAM)  