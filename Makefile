root :
	gcc -o roots src/roots.c -IGSL/include -LGSL/lib -lgsl -lgslcblas
report : report.tex
	xelatex report.tex
	bibtex report
	xelatex report.tex
	xelatex report.tex
