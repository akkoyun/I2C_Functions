#!/bin/sh

set -eu

ROOT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
VERSION_FILE="$ROOT_DIR/VERSION"

if [ "${1-}" != "" ]; then
	VERSION="$1"
	printf '%s\n' "$VERSION" > "$VERSION_FILE"
else
	VERSION="$(tr -d '\r\n' < "$VERSION_FILE")"
fi

case "$VERSION" in
	[0-9][0-9].[0-9][0-9].[0-9][0-9]) ;;
	*)
		echo "Version must use NN.NN.NN format" >&2
		exit 1
		;;
esac

IFS='.' read -r VERSION_MAJOR VERSION_MINOR VERSION_PATCH <<EOF_VERSION
$VERSION
EOF_VERSION

SEMVER_MAJOR=$(printf '%s' "$VERSION_MAJOR" | sed 's/^0*//; s/^$/0/')
SEMVER_MINOR=$(printf '%s' "$VERSION_MINOR" | sed 's/^0*//; s/^$/0/')
SEMVER_PATCH=$(printf '%s' "$VERSION_PATCH" | sed 's/^0*//; s/^$/0/')
SEMVER_VERSION="${SEMVER_MAJOR}.${SEMVER_MINOR}.${SEMVER_PATCH}"

perl -0pi -e "s/#define __I2C_Functions_Version_Major__ \\d+/#define __I2C_Functions_Version_Major__ ${SEMVER_MAJOR}/g; s/#define __I2C_Functions_Version_Minor__ \\d+/#define __I2C_Functions_Version_Minor__ ${SEMVER_MINOR}/g; s/#define __I2C_Functions_Version_Patch__ \\d+/#define __I2C_Functions_Version_Patch__ ${SEMVER_PATCH}/g; s/#define __I2C_Functions_Version__ \"[0-9]{2}\\.[0-9]{2}\\.[0-9]{2}\"/#define __I2C_Functions_Version__ \"${VERSION}\"/g" "$ROOT_DIR/src/Definition.h"

perl -0pi -e "s/version=[0-9]+\\.[0-9]+\\.[0-9]+/version=${SEMVER_VERSION}/g" "$ROOT_DIR/library.properties"

perl -0pi -e "s/\"version\": \"[0-9]+\\.[0-9]+\\.[0-9]+\"/\"version\": \"${SEMVER_VERSION}\"/g" "$ROOT_DIR/library.json"

perl -0pi -e "s/\^V[0-9]{2}\\.[0-9]{2}\\.[0-9]{2}\^/^V${VERSION}^/g; s/#define __I2C_Functions_Version_Major__ [0-9]+/#define __I2C_Functions_Version_Major__ ${SEMVER_MAJOR}/g; s/#define __I2C_Functions_Version_Minor__ [0-9]+/#define __I2C_Functions_Version_Minor__ ${SEMVER_MINOR}/g; s/#define __I2C_Functions_Version_Patch__ [0-9]+/#define __I2C_Functions_Version_Patch__ ${SEMVER_PATCH}/g; s/#define __I2C_Functions_Version__ \"[0-9]{2}\\.[0-9]{2}\\.[0-9]{2}\"/#define __I2C_Functions_Version__ \"${VERSION}\"/g" "$ROOT_DIR/README.md"

echo "Synchronized version ${VERSION} (metadata ${SEMVER_VERSION})"