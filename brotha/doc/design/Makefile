# $Id: Makefile,v 1.2 2002-04-08 09:02:44 nonchocoboy Exp $

NAME=design
default: html pdf

XSLT_TOOL=Saxon
SAXON_VERSION=7.0
XSL_DIR=$(HOME)/software/src/docbook-xsl-1.50.0
#FO_VERSION=XEP

TXT_FILES=	$(NAME).txt
HTML_FILES=	$(NAME).html
PDF_FILES=	$(NAME).pdf

$(NAME).txt: $(NAME).xml # $(NAME).fo
$(NAME).html: $(NAME).xml
$(NAME).pdf: $(NAME).xml $(NAME).fo # $(NAME).tex

include docbook.mk
