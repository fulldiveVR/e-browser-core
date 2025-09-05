APP_NAME="AI Wize Browser"
APP_FILE="${APP_NAME}.app"
APP_VERSION="1.82.2"
CHROME_VERSION="139.1.82.0"

ARCH_APP="${3}"

BUILD_PATH="${1}/${2}_$ARCH_APP"
if [[ "${3}" == "x64" ]]; then
	BUILD_PATH="${1}/${2}"
fi
SRC_ZIP_PATH="$BUILD_PATH/dist/aiwize-v${APP_VERSION}-darwin-${ARCH_APP}.zip"
DST_ZIP_PATH="$BUILD_PATH/dist/aiwize-v${APP_VERSION}-darwin-${ARCH_APP}.zip"
SIGNING_APP_PATH="$BUILD_PATH/dist/$APP_FILE"
SIGNATURE="Developer ID Application: FullDive Corp. (7B7J6CN346)"

PKG_PATH="$BUILD_PATH/AI Wize Browser Packaging"

FRAMEWORK_PATH="$SIGNING_APP_PATH/Contents/Frameworks/${APP_NAME} Framework.framework"
LIBRARIES_PATH="$FRAMEWORK_PATH/Versions/${CHROME_VERSION}/Libraries"
SPARKLE_FRAMEWORK_PATH="$FRAMEWORK_PATH/Versions/${CHROME_VERSION}/Frameworks/Sparkle.framework"
HELPERS_PATH="$FRAMEWORK_PATH/Versions/${CHROME_VERSION}/Helpers"

if [ -d "$SIGNING_APP_PATH" ]; then 
    rm -Rf "$SIGNING_APP_PATH";
fi

ditto -xk "$SRC_ZIP_PATH" "$BUILD_PATH/dist"

cp "release.provisionprofile" "$SIGNING_APP_PATH/Contents/embedded.provisionprofile"

codesign -s "${SIGNATURE}" -f -o runtime --strict --preserve-metadata=entitlements "${LIBRARIES_PATH}/libEGL.dylib"
codesign -s "${SIGNATURE}" -f -o runtime --strict --preserve-metadata=entitlements "${LIBRARIES_PATH}/libvk_swiftshader.dylib"
codesign -s "${SIGNATURE}" -f -o runtime --strict --preserve-metadata=entitlements "${LIBRARIES_PATH}/libGLESv2.dylib"

codesign -s "${SIGNATURE}" -f -o runtime --timestamp "${HELPERS_PATH}/chrome_crashpad_handler"
codesign -s "${SIGNATURE}" -f -o runtime --timestamp "${HELPERS_PATH}/web_app_shortcut_copier"
codesign -s "${SIGNATURE}" -f -o runtime --timestamp "${HELPERS_PATH}/app_mode_loader"

codesign -s "${SIGNATURE}" -f -o runtime --timestamp --entitlements empty-entitlements.plist "${SPARKLE_FRAMEWORK_PATH}/Versions/A/Resources/Autoupdate.app/Contents/MacOS/fileop"
codesign -s "${SIGNATURE}" -f -o runtime --timestamp --entitlements empty-entitlements.plist "${SPARKLE_FRAMEWORK_PATH}/Versions/A/Resources/Autoupdate.app/Contents/MacOS/Autoupdate"

codesign -s "${SIGNATURE}" -f -o runtime --timestamp "$FRAMEWORK_PATH/Versions/${CHROME_VERSION}/Resources/aiwize-darwin"
codesign -s "${SIGNATURE}" -f -o runtime --timestamp "$FRAMEWORK_PATH/Versions/${CHROME_VERSION}/Resources/ollama-darwin"
codesign -s "${SIGNATURE}" -f -o runtime --timestamp "$FRAMEWORK_PATH/Versions/${CHROME_VERSION}/Resources/ollama_llama_server_darwin"
codesign -s "${SIGNATURE}" -f -o runtime --timestamp --entitlements "${PKG_PATH}/helper-plugin-entitlements.plist" "$FRAMEWORK_PATH/Versions/${CHROME_VERSION}/Resources/browser-api-macos-arm"
codesign -s "${SIGNATURE}" -f -o runtime --timestamp --entitlements "${PKG_PATH}/helper-plugin-entitlements.plist" "$FRAMEWORK_PATH/Versions/${CHROME_VERSION}/Resources/qdrant-macos"

codesign -s "${SIGNATURE}" -f -o runtime --timestamp "$SIGNING_APP_PATH/Contents/Library/LaunchServices/com.aiwize.Browser.UpdaterPrivilegedHelper"

codesign -s "${SIGNATURE}" -f -o runtime --timestamp --deep --strict "${HELPERS_PATH}/${APP_NAME} Helper (Alerts).app"
codesign -s "${SIGNATURE}" -f -o runtime --timestamp --deep --strict --entitlements "${PKG_PATH}/helper-gpu-entitlements.plist" "${HELPERS_PATH}/${APP_NAME} Helper (GPU).app"
codesign -s "${SIGNATURE}" -f -o runtime --timestamp --deep --strict --entitlements "${PKG_PATH}/helper-plugin-entitlements.plist" "${HELPERS_PATH}/${APP_NAME} Helper (Plugin).app"
codesign -s "${SIGNATURE}" -f -o runtime --timestamp --deep --strict --entitlements "${PKG_PATH}/helper-renderer-entitlements.plist" "${HELPERS_PATH}/${APP_NAME} Helper (Renderer).app"
codesign -s "${SIGNATURE}" -f -o runtime --timestamp --deep --strict "${HELPERS_PATH}/${APP_NAME} Helper.app"

codesign -s "${SIGNATURE}" -f -o runtime --timestamp --preserve-metadata=entitlements "$SPARKLE_FRAMEWORK_PATH"
codesign -s "${SIGNATURE}" -f -o runtime --timestamp --preserve-metadata=entitlements "$FRAMEWORK_PATH"

codesign -s "${SIGNATURE}" -f -o runtime --timestamp --strict --entitlements app-entitlements.plist "$SIGNING_APP_PATH"

echo "\n#### CHECK ###"
codesign -d -vvvv "$SIGNING_APP_PATH"
echo "\n### 1"
codesign -vvv --deep --strict "$SIGNING_APP_PATH"
echo "\n### 2"
codesign -d --entitlements :- "$SIGNING_APP_PATH"

ditto -c -k --keepParent "$SIGNING_APP_PATH" "$DST_ZIP_PATH"

if [[ "${4}" == "true" ]]; then
    echo "\n#### NOTARIZATION ###"
    xcrun notarytool submit "$DST_ZIP_PATH" --keychain-profile "notarytool-password" --wait
    xcrun stapler staple "$SIGNING_APP_PATH"
    rm "$DST_ZIP_PATH";
    ditto -c -k --keepParent "$SIGNING_APP_PATH" "$DST_ZIP_PATH"
    echo "\n#### FINISHED:\n$DST_ZIP_PATH"
fi
