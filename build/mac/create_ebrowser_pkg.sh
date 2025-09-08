HOME_PATH="/Users/managerdark"
APP_NAME="AI Wize Browser"
APP_VERSION="1.82.2"
SIGNATURE="Developer ID Installer: FullDive Corp. (7B7J6CN346)"
KEYCHAIN="$HOME_PATH/Library/Keychains/login.keychain-db"
BUILD_PATH="/Users/managerdark/brave-browser/src/out/Release_arm64"
DIST_PATH="$BUILD_PATH/dist"
UNSIGNED_PATH="$DIST_PATH/unsigned"
APP_PATH="$DIST_PATH/$APP_NAME.app"
PKG_PATH="$DIST_PATH/$APP_NAME.pkg"
PKG_ROOT="/Users/managerdark/brave-browser/src/brave/build/mac/pkg_root"
DST_ZIP_PATH="$DIST_PATH/aiwize_installer-v${APP_VERSION}.zip"

if [ -d "$UNSIGNED_PATH" ]; then 
    rm -Rf "$UNSIGNED_PATH";
fi
mkdir "$UNSIGNED_PATH"

./create_pkg.sh "$APP_PATH" "/Users/managerdark/brave-browser/src/brave/build/mac/pkg-scripts" "$BUILD_PATH/Brave Browser Component.plist" "$UNSIGNED_PATH/$APP_NAME.pkg"
./sign_pkg.sh "$UNSIGNED_PATH/$APP_NAME.pkg" "$PKG_PATH" "$KEYCHAIN" "$SIGNATURE"

xcrun notarytool submit "$PKG_PATH" --keychain-profile "notarytool-password" --wait
xcrun stapler staple "$PKG_PATH"
ditto -c -k "$PKG_PATH" "$DST_ZIP_PATH"

if [ -d "$UNSIGNED_PATH" ]; then 
    rm -Rf "$UNSIGNED_PATH";
fi

if [ -d "$PKG_ROOT" ]; then 
    rm -Rf "$PKG_ROOT";
fi
