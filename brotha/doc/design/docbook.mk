# ************** <auto-copyright.pl BEGIN do not edit this line> **************
#
# VR Juggler is (C) Copyright 1998, 1999, 2000 by Iowa State University
#
# Original Authors:
#   Allen Bierbaum, Christopher Just,
#   Patrick Hartling, Kevin Meinert,
#   Carolina Cruz-Neira, Albert Baker
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#
# -----------------------------------------------------------------
# File:          $RCSfile: docbook.mk,v $
# Date modified: $Date: 2002-04-08 04:24:55 $
# Version:       $Revision: 1.2 $
# -----------------------------------------------------------------
#
# *************** <auto-copyright.pl END do not edit this line> ***************

.SUFFIXES: .html .xml .pdf .tex .fo .txt

XALAN_VERSION?=	20020214
SAXON_VERSION?=	6.5.1

DVIPDF?=	dvipdf
DVIPS?=		dvips
FOP?=		sh $(DOCBOOK_ROOT)/fop/fop.sh
JADE?=		openjade -V tex-backend
JADEPROC?=	$(DOCBOOK_ROOT)/jadeproc.pl
JADETEX?=	$(TEX_BINDIR)/jadetex
PDFJADETEX?=	$(TEX_BINDIR)/pdfjadetex
PDFLATEX?=	$(TEX_BINDIR)/pdflatex
PDFTEX?=	$(TEX_BINDIR)/pdftex
PDFXMLTEX?=	$(TEX_BINDIR)/pdfxmltex
RASTERIZER?=	$(DOCBOOK_ROOT)/batik-1.5/svgrasterizer
RM=		rm -f
SAXON?=		$(DOCBOOK_ROOT)/saxon-$(SAXON_VERSION)/saxon.sh
TEX_DIR?=	$(DOCBOOK_ROOT)/TeX
TEX_BINDIR?=	$(TEX_DIR)/bin/i386-linux
TEX_ENV?=	PATH=$(TEX_BINDIR):$(PATH) VARTEXMF=$(TEX_DIR)/texmf-var
XALAN?=		$(DOCBOOK_ROOT)/xalan-j_$(XALAN_VERSION)/bin/xalan.sh
XEP?=		sh $(DOCBOOK_ROOT)/XEP/run.sh
XSLTPROC?=	/usr/bin/xsltproc

FO_VERSION?=	FOP
XSLT_TOOL?=	Xalan

# Use one of the following depending on what will be processing the generated
# FO.  The default is to use FOP.  XEP or Passive TeX can be used instead by
# defining $(USE_XEP) or $(USE_PASSIVE_TEX) respectively.
ifeq ($(FO_VERSION), FOP)
   XALAN_FO_PARAMS=	-PARAM fop.extensions "1"
   SAXON_FO_PARAMS=	fop.extensions=1
else
ifeq ($(FO_VERSION), XEP)
   XALAN_FO_PARAMS=	-PARAM xep.extensions "1"
   SAXON_FO_PARAMS=	xep.extensions=1
else
ifeq ($(FO_VERSION), PASSIVE_TEX)
   XALAN_FO_PARAMS=	-PARAM passivetex.extensions "1"		\
			-PARAM tex.math.in.alt "latex"
   SAXON_FO_PARAMS=	passivetex.extensions=1 tex.math.in.alt=latex
endif # PASSIVE_TEX
endif # XEP
endif # FOP

SAXON_HTML_PARAMS=	html.stylesheet=base_style.css
XALAN_HTML_PARAMS=	-PARAM html.stylesheet "base_style.css"

XALAN_TXT_PARAMS=	-PARAM page.margin.bottom "0in"	\
			-PARAM page.margin.inner "0in"	\
			-PARAM page.margin.outer "0in"	\
			-PARAM page.margin.top "0in"	\
			-PARAM paper.type "A5"

DOCBOOK_ROOT?=	/home/vr/Juggler/docbook
SGML_ROOT?=	/usr/share/sgml/docbook

DB_SGML_DTD?=	$(DOCBOOK_ROOT)/docbook-sgml-4.1.dtd
DSSSL_DIR?=	$(DOCBOOK_ROOT)/docbook-dsssl-1.76
XSL_DIR?=	$(DOCBOOK_ROOT)/docbook-xsl-1.49

ifdef NEED_DB_IMAGES
LINK_DEPS=	images
endif

txt: $(TXT_FILES)

html: $(LINK_DEPS) $(HTML_FILES)

chunk-html:
	for file in $(XML_FILES) ; do \
            dir=`echo $$file | sed -e 's/\.xml//'` ; \
            if [ ! -d $$dir ] ; then mkdir $$dir ; fi ; \
            cur_dir=`pwd` ; \
            cd $$dir ; \
            $(SAXON) -i $$cur_dir/$$file -xsl $(XSL_DIR)/html/chunk.xsl \
              $(SAXON_HTML_PARAMS) $(EXTRA_SAXON_HTML_PARAMS) ; \
            cd $$cur_dir ; \
        done

pdf: $(LINK_DEPS) $(PDF_FILES)

# The method for specifying a path to the images that come with the DocBook
# XSL stylesheets sucks.  It requires a path relative to the current directory,
# and we do not necessarily know how to get to $(XSL_DIR) relative to the
# current directory.  This hack with a symlink works around that problem.
images:
	ln -s $(XSL_DIR)/images ./

install-txt: $(TXT_FILES)
ifndef prefix
	$(error "No prefix set!")
else
	if [ ! -d "$(prefix)" ]; then mkdir -p $(prefix); fi
	cp $(TXT_FILES) $(prefix)/
endif

install-html: $(LINK_DEPS) $(HTML_FILES)
ifndef prefix
	$(error "No prefix set!")
else
	if [ ! -d "$(prefix)" ]; then mkdir -p $(prefix); fi
	cp $(HTML_FILES) $(prefix)/
ifdef INSTALL_FILES
	cp $(INSTALL_FILES) $(prefix)/
endif
ifdef INSTALL_DIRS
	cp -r $(INSTALL_DIRS) $(prefix)
endif
ifdef NEED_DB_IMAGES
	cp -rH images $(prefix)/
endif
endif

install-chunk-html:
ifndef prefix
	$(error "No prefix set!")
else
	if [ ! -d "$(prefix)" ]; then mkdir -p $(prefix); fi
	for file in $(XML_FILES) ; do \
            dir=`echo $$file | sed -e 's/\.xml//'` ; \
            cp -r $$dir $(prefix)/ ; \
            if [ ! -z "$(INSTALL_FILES)" ]; then \
                cp $(INSTALL_FILES) $(prefix)/$$dir ; \
            fi ; \
            if [ ! -z "$(NEED_DB_IMAGES)" ]; then \
                cp -rH images $(prefix)/$$dir ; \
            fi ; \
            if [ ! -z "$(INSTALL_DIRS)" ]; then \
                cp -r $(INSTALL_DIRS) $(prefix)/$$dir ; \
            fi ; \
          done
endif

install-pdf: $(PDF_FILES)
ifndef prefix
	$(error "No prefix set!")
else
	cp $(PDF_FILES) $(prefix)/
endif

install install-all:
	$(MAKE) install-html
	$(MAKE) install-chunk-html
	$(MAKE) install-pdf

# Image conversions -----------------------------------------------------------

%.png: %.svg
	$(RASTERIZER) -bg 255.255.255.255 -m png $<

%.jpg %.jpeg: %.svg
	$(RASTERIZER) -q .75 -bg 255.255.255.255 -m jpg $<

# Basic XSL conversions -------------------------------------------------------

.xml.html:
ifeq ($(XSLT_TOOL), Xalan)
	$(XALAN) -in $< -xsl $(XSL_DIR)/html/docbook.xsl -out $@	\
          $(XALAN_HTML_PARAMS) $(EXTRA_XALAN_HTML_PARAMS)
else
	$(SAXON) -i $< -xsl $(XSL_DIR)/html/docbook.xsl -o $@		\
          $(SAXON_HTML_PARAMS) $(EXTRA_SAXON_HTML_PARAMS)
endif

.xml.fo:
ifeq ($(XSLT_TOOL), Xalan)
	$(XALAN) -in $< -xsl $(XSL_DIR)/fo/docbook.xsl -out $@		\
          $(XALAN_FO_PARAMS) $(EXTRA_XALAN_FO_PARAMS)
else
	$(SAXON) -i $< -xsl $(XSL_DIR)/fo/docbook.xsl -o $@		\
          $(SAXON_FO_PARAMS) $(EXTRA_SAXON_FO_PARAMS)
endif

.xml.txt:
ifeq ($(XSLT_TOOL), Xalan)
	$(XALAN) -in $< -xsl $(XSL_DIR)/fo/docbook.xsl -out $@		\
          $(XALAN_TXT_PARAMS) $(EXTRA_XALAN_TXT_PARAMS)
else
	$(SAXON) -i $< -xsl $(XSL_DIR)/fo/docbook.xsl -o $@		\
          $(SAXON_TXT_PARAMS) $(EXTRA_SAXON_TXT_PARAMS)
endif
	$(FOP) -fo $< -txt $@

# Generate a PDF file from an FO file using FOP.
ifeq ($(FO_VERSION), FOP)
.fo.pdf:
	$(FOP) $< $@

.fo.txt:
	$(FOP) -fo $< -txt $@
endif

# Generate a PDF file from an XML file using FOP.
#.xml.pdf:
#	$(FOP) -xml $< -xsl $(XSL_DIR)/fo/docbook.xsl -pdf $@

# -----------------------------------------------------------------------------

# Jade/JadeTex conversions ----------------------------------------------------

# Generate a TeX file using Jade.
ifdef USE_JADEPROC
.xml.pdf:
	$(TEX_ENV) $(JADEPROC) -i $< -o $@ -d $(DB_SGML_DTD)		\
          -s $(DSSSL_DIR)/print/docbook.dsl
         
else
.xml.tex:
	$(JADE) -t tex -d $(DSSSL_DIR)/print/docbook.dsl $<

# $(PDFJADETEX) has to be run twice for page references to be calculated.  :(
.tex.pdf:
	-$(TEX_ENV) $(PDFJADETEX) $<
endif

# -----------------------------------------------------------------------------

# PassiveTeX conversions ------------------------------------------------------

# Generate a PDF file from an XML file using PassiveTeX.  This one requires
# that a simple TeX file be generated from the XML first (see below).
ifeq ($(FO_VERSION), PASSIVE_TEX)
.fo.pdf:
	$(TEX_ENV) $(PDFXMLTEX) $*.fo
#	$(TEX_ENV) $(PDFXMLTEX) $*.fo

# Generate a TeX file for use with PassiveTeX.
#.xml.tex:
#	@echo "Generating $*.tex from $<"
#	@echo '\def\xmlfile{$*.fo}' >$*.tex
#	@echo '\input xmltex' >>$*.tex
endif

# -----------------------------------------------------------------------------

# RenderX XEP conversions -----------------------------------------------------

# Generate a PDF file using XEP from RenderX.  This requires that an FO file
# be generated first.
ifeq ($(FO_VERSION), XEP)
.fo.pdf:
	$(XEP) $*.fo
endif

# -----------------------------------------------------------------------------

clean:
	$(RM) *.aux *.out *.tex *.log *.fo *~

clobber:
	@$(MAKE) clean
	$(RM) *.html *.pdf $(LINK_DEPS)
