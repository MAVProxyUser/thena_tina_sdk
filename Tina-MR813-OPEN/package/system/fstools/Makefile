#
# Copyright (C) 2014-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=fstools
PKG_VERSION:=2016-01-10

PKG_RELEASE=$(PKG_SOURCE_VERSION)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL=$(OPENWRT_GIT)/project/fstools.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=96415afecef35766332067f4205ef3b2c7561d21
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz
CMAKE_INSTALL:=1

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=

PKG_USE_MIPS16:=0

PKG_MAINTAINER:=John Crispin <blogic@openwrt.org>

PKG_PREPARED_DEPENDS += CONFIG_USE_DM_VERITY

include $(BUILD_DIR)/package.mk
include $(BUILD_DIR)/cmake.mk

TARGET_CFLAGS += $(if $(CONFIG_USE_GLIBC),-pthread)
TARGET_LDFLAGS += $(if $(CONFIG_USE_GLIBC),-lrt)
CMAKE_OPTIONS += $(if $(CONFIG_FSTOOLS_UBIFS_EXTROOT),-DCMAKE_UBIFS_EXTROOT=y)
CMAKE_OPTIONS += $(if $(CONFIG_FSTOOLS_ROOTFS_RW),-DCMAKE_ROOTFS_RW=y)
CMAKE_OPTIONS += $(if $(CONFIG_USE_DM_VERITY),-DDM_VERITY_ENABLED=y)

define Package/fstools
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=+ubox +USE_GLIBC:librt +NAND_SUPPORT:ubi-utils
  DEPENDS+= @SYSTEM_INIT_PROCD
  TITLE:=OpenWrt filesystem tools
  MENU:=1
endef

define Package/fstools/config
	config FSTOOLS_UBIFS_EXTROOT
		depends on PACKAGE_fstools
		depends on NAND_SUPPORT
		bool "Support extroot functionality with UBIFS"
		default y
		help
			This option makes it possible to use extroot functionality if the root filesystem resides on an UBIFS partition
	config FSTOOLS_ROOTFS_RW
		depends on PACKAGE_fstools
		bool "Support rootfs mount as writable"
		default n
		help
		  If set, mount rootfs as writable.
		  If unsure, say no.
endef

define Package/block-mount
  SECTION:=base
  CATEGORY:=Base system
  TITLE:=Block device mounting and checking
  DEPENDS:=+ubox +libubox +libuci
  DEPENDS+= @SYSTEM_INIT_PROCD
endef

define Package/fstools/install
	$(INSTALL_DIR) $(1)/sbin $(1)/lib

	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/{mount_root,jffs2reset,snapshot_tool} $(1)/sbin/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libfstools.so $(1)/lib/
	$(INSTALL_BIN) ./files/snapshot $(1)/sbin/
	$(LN) jffs2reset $(1)/sbin/jffs2mark
endef

define Package/block-mount/install
	$(INSTALL_DIR) $(1)/sbin $(1)/lib $(1)/usr/sbin $(1)/etc/hotplug.d/block $(1)/etc/init.d/ $(1)/etc/uci-defaults/

	$(INSTALL_BIN) ./files/fstab.init $(1)/etc/init.d/fstab
	$(INSTALL_DATA) ./files/fstab.default $(1)/etc/uci-defaults/10-fstab
	$(INSTALL_DATA) ./files/mount.hotplug $(1)/etc/hotplug.d/block/10-mount

	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/block $(1)/sbin/
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libblkid-tiny.so $(1)/lib/
	$(LN) ../../sbin/block $(1)/usr/sbin/swapon
	$(LN) ../../sbin/block $(1)/usr/sbin/swapoff

endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/*.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libubi-utils.a $(1)/usr/lib/
endef

$(eval $(call BuildPackage,fstools))
$(eval $(call BuildPackage,block-mount))
