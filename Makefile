all: stm32.html
stm32.html: stm32.md
	pandoc stm32.md -o stm32.html -t html5 -strue --css=''

