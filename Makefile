USER = scagle
KEYBOARDS = ergodox_ez

# keymap path
PATH_ergodox_ez = ergodox_ez

# keyboard name
NAME_ergodox_ez = ergodox_ez

all: $(KEYBOARDS)

.PHONY: $(KEYBOARDS)
$(KEYBOARDS):
	# cleanup old symlinks
	git --git-dir qmk_firmware/.git reset --hard
	git --git-dir qmk_firmware/.git clean -xfd

	# add new symlinks
	ln -s $(shell pwd)/user qmk_firmware/users/$(USER)
	ln -s $(shell pwd)/keyboards/$@ qmk_firmware/keyboards/$(PATH_$@)/keymaps/$(USER)

	# run lint check
	cd qmk_firmware; qmk lint -km $(USER) -kb $(NAME_$@) --strict
	
	# run build
	make BUILD_DIR=$(shell pwd)/build -j1 -C qmk_firmware $(NAME_$@):$(USER)

#clean:
#	rm -rf ./qmk_firmware/
#	rm -rf ./build/
#	rm -rf qmk_firmware/keyboards/$(PATH_lily58)/keymaps/$(USER)
#	rm -rf qmk_firmware/keyboards/$(PATH_kyria)/keymaps/$(USER)
#	rm -rf qmk_firmware/keyboards/$(PATH_sweep)/keymaps/$(USER)
#	rm -rf qmk_firmware/users/$(USER)
#
#
