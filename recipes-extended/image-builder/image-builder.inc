SUMMARY = "Xen Image Builder"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=d2794c0df5b907fdace235a619d80314"

BRANCH ?= "xlnx_rel_v2023.1"
REPO ?= "git://github.com/Xilinx/imagebuilder.git;protocol=https"
SRCREV ?= "37ba04b63cb2c01d8e683f31a9eb3878f1e80305"
BRANCHARG = "${@['nobranch=1', 'branch=${BRANCH}'][d.getVar('BRANCH') != '']}"
SRC_URI = "${REPO};${BRANCHARG}"

S = "${WORKDIR}/git"

inherit deploy

DEPENDS += " \
    u-boot-mkimage-native \
    "

RDEPENDS:${PN} += " \
    bash \
    "

do_install () {
    install -d ${D}${bindir}
    chmod -R 777 ${S}/scripts/*
    install -m 0755 ${S}/scripts/* ${D}${bindir}
    ln -sf ${D}${bindir}/uboot-script-gen uboot-script-gen
}

do_deploy() {
	:
}

do_deploy:class-native() {
    install -d ${DEPLOYDIR}
    install -m 0755 ${S}/scripts/uboot-script-gen ${DEPLOYDIR}/
}

addtask do_deploy after do_install

BBCLASSEXTEND = "native nativesdk"
