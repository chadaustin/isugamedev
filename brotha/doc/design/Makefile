# $Id: Makefile,v 1.5 2002-04-12 07:03:04 nonchocoboy Exp $

NAME=design
default: pdf

XSLT_TOOL=Saxon
SAXON_VERSION=7.0
XSL_DIR=$(HOME)/software/src/docbook-xsl-1.50.0
#FO_VERSION=XEP
USE_JADEPROC=1

TXT_FILES=	$(NAME).txt
HTML_FILES=	$(NAME).html
PDF_FILES=	$(NAME).pdf

SVG_IMAGES= \
	client_components \
	server_components \
	gamelogic_classes \
	network_classes \
	reportserver_classes \
	sound_classes \
	thread_classes

SVG_IMAGES := $(addprefix figures/, $(addsuffix .svg, $(SVG_IMAGES)))

IMAGES = $(SVG_IMAGES:.svg=.png)

$(NAME).txt: $(NAME).xml $(IMAGES)
$(NAME).html: $(NAME).xml $(IMAGES)
#$(NAME).pdf: $(NAME).xml $(NAME).fo $(IMAGES)
$(NAME).pdf: $(NAME).xml $(IMAGES)


include docbook.mk
