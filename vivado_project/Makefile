check_defined = $(if $(firstword $(strip $(1))),,$(error Undefined parameter => cmd "make help" for details))

#VIVADO_HLS_EXE := vivado_hls
VIVADO_HLS_EXE := vitis_hls

export dir_project     := $(shell pwd)
export dir_src         := $(dir_project)/design
export dir_doc         := $(dir_project)/doc
export dir_script      := $(dir_project)/script
export dir_work       := $(dir_project)/work

$(dir_work) :
	mkdir -p $(dir_work)

doc :
	@evince $(dir_doc)/ug902-vivado-high-level-synthesis.pdf &

reset :
	rm -rf $(dir_work) \
	rm -rf ~/.$(VIVADO_HLS_EXE)

clean :
	$(call check_defined, $(HLS_TOP))
	rm -rf $(dir_work)/$(HLS_TOP)

csim : $(dir_work)
	$(call check_defined, $(HLS_TOP))
	cd $(dir_work) && \
		hls_step=1 $(VIVADO_HLS_EXE) -f $(dir_script)/$(HLS_TOP).tcl

synth : $(dir_work)
	$(call check_defined, $(HLS_TOP))
	cd $(dir_work) && \
		rm -rf $(dir_work)/$(HLS_TOP)/Solution1/impl && \
		rm -rf $(dir_work)/$(HLS_TOP)/Solution1/syn && \
		hls_step=2 $(VIVADO_HLS_EXE) -f $(dir_script)/$(HLS_TOP).tcl

open :
	$(call check_defined, $(HLS_TOP))
	cd $(dir_work) && \
		$(VIVADO_HLS_EXE) -p $(dir_work)/$(HLS_TOP)

simu :
	$(call check_defined, $(HLS_TOP))
	cd $(dir_work) && \
		$(VIVADO_HLS_EXE) -f $(dir_script)/cosim.tcl

cosim :
	$(call check_defined, $(HLS_TOP))
	cd $(dir_work) && \
		$(VIVADO_HLS_EXE) -f $(dir_script)/cosim.tcl

open_wave :
	$(call check_defined, $(HLS_TOP))
	cd $(dir_work)/$(HLS_TOP)/solution1/sim/verilog && \
		vivado -source $(dir_script)/open_wave.tcl

export_ip :
	$(call check_defined, $(HLS_TOP))
	cd $(dir_work) && \
	hls_step=3 $(VIVADO_HLS_EXE) -f $(dir_script)/$(HLS_TOP).tcl
	@echo ""
	@echo "[IP Implementation Files]"
	@echo "=> $(dir_work)/$(HLS_TOP)/solution1/impl :"
	@ls -al $(dir_work)/$(HLS_TOP)/solution1/impl

generate_project :
	script/generate_project

help :
	@echo ""
	@echo "## VIVADO HLS Help Makefile"
	@echo "## Autor : Mathieu Lebon (ML)"
	@echo "## Date  : 12/2020"
	@echo ""
	@echo "make doc            : open vivado hls documentation"
	@echo ""
	@echo "make HLS_TOP=[TOP] [CMD]"
	@echo ""
	@echo "     [TOP] "
	@echo "            filter_std : standard filter"
	@echo "            filter_sym : symmetric filter"
	@echo "            poly_1     : polyphase filter 1"
	@echo "            poly_2     : polyphase filter 2"
	@echo "            poly_3     : polyphase filter 3"
	@echo "            fft        : fft"
	@echo ""
	@echo "     [CMD] "
	@echo "             csim      : C++/SystemC simulation"
	@echo "             synth     : vivado hls synthesis"
	@echo "             open      : vivado hls open"
	@echo "             cosim     : C++/RTL simulation"
	@echo "             open_wave : Open co-simulation waves (after cosim)"
	@echo "             export_ip : export ip for vivado"

.PHONY : doc

