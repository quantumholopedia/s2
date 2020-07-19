#!/usr/bin/env bash

if ! type -p "realpath" &>/dev/null; then
	realpath() {
		python -c 'import os, sys; print "\n".join ([os.path.realpath (p) for p in sys.argv [1:]])' "$@"
	}
	export -f realpath
fi

SRCROOT="$(realpath "$(dirname "$0")")"
CMAKE_DIR="${SRCROOT}/build"

die() {
	local rc="$?"
	echo "$@" >&2
	exit "${rc}"
}

do_configure() {
	cmake -DCMAKE_INSTALL_PREFIX="${SRCROOT}" -GXcode -B "${CMAKE_DIR}"
}

do_build() {
	cmake --build "${CMAKE_DIR}" --config Release -t s2
}

do_install() {
	cmake --install "${CMAKE_DIR}"
}

do_all() {
	do_configure && do_build && do_install
}

do_clean() {
	rm -rf "${CMAKE_DIR}" "${SRCROOT}/bin"
}

[ "$#" -eq 0 ] && set -- all
while [ "$#" -gt 0 ]; do
	action="$1"; handler="do_$1"; shift

	type "${handler}" &>/dev/null || die "Unknown action: '${action}'"
	"${handler}" || die "Action '${action}' failed"
done