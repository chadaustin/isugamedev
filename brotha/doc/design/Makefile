# $Id: Makefile,v 1.1 2002-04-05 04:33:59 nonchocoboy Exp $

NAME=design
default: html pdf

XSLT_TOOL=Saxon
FO_VERSION=XEP

TXT_FILES=	$(NAME).txt
HTML_FILES=	$(NAME).html
PDF_FILES=	$(NAME).pdf

$(NAME).txt: $(NAME).xml # $(NAME).fo
$(NAME).html: $(NAME).xml
$(NAME).pdf: $(NAME).xml $(NAME).fo # $(NAME).tex

include docbook.mk
