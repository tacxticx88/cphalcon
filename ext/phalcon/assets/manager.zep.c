
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/file.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Assets\Manager
 *
 * Manages collections of CSS/Javascript assets
 */
ZEPHIR_INIT_CLASS(Phalcon_Assets_Manager) {

	ZEPHIR_REGISTER_CLASS(Phalcon\\Assets, Manager, phalcon, assets_manager, phalcon_assets_manager_method_entry, 0);

	zend_declare_property_null(phalcon_assets_manager_ce, SL("collections"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_assets_manager_ce, SL("container"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Options configure
	 * @var array
	 */
	zend_declare_property_null(phalcon_assets_manager_ce, SL("options"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var bool
	 */
	zend_declare_property_bool(phalcon_assets_manager_ce, SL("implicitOutput"), 1, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(phalcon_assets_manager_ce TSRMLS_CC, 1, phalcon_di_injectionawareinterface_ce);
	return SUCCESS;

}

/**
 * Phalcon\Assets\Manager
 */
PHP_METHOD(Phalcon_Assets_Manager, __construct) {

	zval *options_param = NULL;
	zval options;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&options);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &options_param);

	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}


	zephir_update_property_zval(this_ptr, SL("options"), &options);
	ZEPHIR_MM_RESTORE();

}

/**
 * Adds a raw asset to the manager
 *
 *<code>
 * $assets->addAsset(
 *     new Phalcon\Assets\Asset("css", "css/style.css")
 * );
 *</code>
 */
PHP_METHOD(Phalcon_Assets_Manager, addAsset) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *asset, asset_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&asset_sub);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &asset);



	ZEPHIR_CALL_METHOD(&_0, asset, "gettype", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addassetbytype", NULL, 0, &_0, asset);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Adds a asset by its type
 *
 *<code>
 * $assets->addAssetByType(
 *     "css",
 *     new \Phalcon\Assets\Asset\Css("css/style.css")
 * );
 *</code>
 */
PHP_METHOD(Phalcon_Assets_Manager, addAssetByType) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *type_param = NULL, *asset, asset_sub, collection, _0;
	zval type;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&asset_sub);
	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &type_param, &asset);

	if (UNEXPECTED(Z_TYPE_P(type_param) != IS_STRING && Z_TYPE_P(type_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'type' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(type_param) == IS_STRING)) {
		zephir_get_strval(&type, type_param);
	} else {
		ZEPHIR_INIT_VAR(&type);
		ZVAL_EMPTY_STRING(&type);
	}


	ZEPHIR_OBS_VAR(&collection);
	zephir_read_property(&_0, this_ptr, SL("collections"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&collection, &_0, &type, 0 TSRMLS_CC))) {
		ZEPHIR_INIT_NVAR(&collection);
		object_init_ex(&collection, phalcon_assets_collection_ce);
		ZEPHIR_CALL_METHOD(NULL, &collection, "__construct", NULL, 131);
		zephir_check_call_status();
		zephir_update_property_array(this_ptr, SL("collections"), &type, &collection TSRMLS_CC);
	}
	ZEPHIR_CALL_METHOD(NULL, &collection, "add", NULL, 132, asset);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Adds a Css asset to the 'css' collection
 *
 *<code>
 * $assets->addCss("css/bootstrap.css");
 * $assets->addCss("http://bootstrap.my-cdn.com/style.css", false);
 *</code>
 */
PHP_METHOD(Phalcon_Assets_Manager, addCss) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool filter, autoVersion;
	zval *path_param = NULL, *local = NULL, local_sub, *filter_param = NULL, *attributes = NULL, attributes_sub, *version_param = NULL, *autoVersion_param = NULL, __$true, __$null, _0, _1, _2, _3;
	zval path, version;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&version);
	ZVAL_UNDEF(&local_sub);
	ZVAL_UNDEF(&attributes_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 5, &path_param, &local, &filter_param, &attributes, &version_param, &autoVersion_param);

	if (UNEXPECTED(Z_TYPE_P(path_param) != IS_STRING && Z_TYPE_P(path_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'path' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(path_param) == IS_STRING)) {
		zephir_get_strval(&path, path_param);
	} else {
		ZEPHIR_INIT_VAR(&path);
		ZVAL_EMPTY_STRING(&path);
	}
	if (!local) {
		local = &local_sub;
		local = &__$true;
	}
	if (!filter_param) {
		filter = 1;
	} else {
		filter = zephir_get_boolval(filter_param);
	}
	if (!attributes) {
		attributes = &attributes_sub;
		attributes = &__$null;
	}
	if (!version_param) {
		ZEPHIR_INIT_VAR(&version);
		ZVAL_STRING(&version, "");
	} else {
		zephir_get_strval(&version, version_param);
	}
	if (!autoVersion_param) {
		autoVersion = 0;
	} else {
		autoVersion = zephir_get_boolval(autoVersion_param);
	}


	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, phalcon_assets_asset_css_ce);
	if (filter) {
		ZVAL_BOOL(&_1, 1);
	} else {
		ZVAL_BOOL(&_1, 0);
	}
	if (autoVersion) {
		ZVAL_BOOL(&_2, 1);
	} else {
		ZVAL_BOOL(&_2, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 127, &path, local, &_1, attributes, &version, &_2);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "css");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addassetbytype", NULL, 0, &_3, &_0);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Adds a raw inline code to the manager
 */
PHP_METHOD(Phalcon_Assets_Manager, addInlineCode) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *code, code_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&code_sub);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &code);



	ZEPHIR_CALL_METHOD(&_0, code, "gettype", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addinlinecodebytype", NULL, 0, &_0, code);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Adds an inline code by its type
 */
PHP_METHOD(Phalcon_Assets_Manager, addInlineCodeByType) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *type_param = NULL, *code, code_sub, collection, _0;
	zval type;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&type);
	ZVAL_UNDEF(&code_sub);
	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &type_param, &code);

	if (UNEXPECTED(Z_TYPE_P(type_param) != IS_STRING && Z_TYPE_P(type_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'type' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(type_param) == IS_STRING)) {
		zephir_get_strval(&type, type_param);
	} else {
		ZEPHIR_INIT_VAR(&type);
		ZVAL_EMPTY_STRING(&type);
	}


	ZEPHIR_OBS_VAR(&collection);
	zephir_read_property(&_0, this_ptr, SL("collections"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&collection, &_0, &type, 0 TSRMLS_CC))) {
		ZEPHIR_INIT_NVAR(&collection);
		object_init_ex(&collection, phalcon_assets_collection_ce);
		ZEPHIR_CALL_METHOD(NULL, &collection, "__construct", NULL, 131);
		zephir_check_call_status();
		zephir_update_property_array(this_ptr, SL("collections"), &type, &collection TSRMLS_CC);
	}
	ZEPHIR_CALL_METHOD(NULL, &collection, "addinline", NULL, 133, code);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Adds an inline Css to the 'css' collection
 */
PHP_METHOD(Phalcon_Assets_Manager, addInlineCss) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *content_param = NULL, *filter = NULL, filter_sub, *attributes = NULL, attributes_sub, __$true, __$null, _0, _1;
	zval content;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content);
	ZVAL_UNDEF(&filter_sub);
	ZVAL_UNDEF(&attributes_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &content_param, &filter, &attributes);

	zephir_get_strval(&content, content_param);
	if (!filter) {
		filter = &filter_sub;
		filter = &__$true;
	}
	if (!attributes) {
		attributes = &attributes_sub;
		attributes = &__$null;
	}


	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, phalcon_assets_inline_css_ce);
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 128, &content, filter, attributes);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "css");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addinlinecodebytype", NULL, 0, &_1, &_0);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Adds an inline javascript to the 'js' collection
 */
PHP_METHOD(Phalcon_Assets_Manager, addInlineJs) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *content_param = NULL, *filter = NULL, filter_sub, *attributes = NULL, attributes_sub, __$true, __$null, _0, _1;
	zval content;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content);
	ZVAL_UNDEF(&filter_sub);
	ZVAL_UNDEF(&attributes_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &content_param, &filter, &attributes);

	zephir_get_strval(&content, content_param);
	if (!filter) {
		filter = &filter_sub;
		filter = &__$true;
	}
	if (!attributes) {
		attributes = &attributes_sub;
		attributes = &__$null;
	}


	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, phalcon_assets_inline_js_ce);
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 129, &content, filter, attributes);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "js");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addinlinecodebytype", NULL, 0, &_1, &_0);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Adds a javascript asset to the 'js' collection
 *
 *<code>
 * $assets->addJs("scripts/jquery.js");
 * $assets->addJs("http://jquery.my-cdn.com/jquery.js", false);
 *</code>
 */
PHP_METHOD(Phalcon_Assets_Manager, addJs) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool filter, autoVersion;
	zval *path_param = NULL, *local = NULL, local_sub, *filter_param = NULL, *attributes = NULL, attributes_sub, *version_param = NULL, *autoVersion_param = NULL, __$true, __$null, _0, _1, _2, _3;
	zval path, version;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&version);
	ZVAL_UNDEF(&local_sub);
	ZVAL_UNDEF(&attributes_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 5, &path_param, &local, &filter_param, &attributes, &version_param, &autoVersion_param);

	if (UNEXPECTED(Z_TYPE_P(path_param) != IS_STRING && Z_TYPE_P(path_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'path' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(path_param) == IS_STRING)) {
		zephir_get_strval(&path, path_param);
	} else {
		ZEPHIR_INIT_VAR(&path);
		ZVAL_EMPTY_STRING(&path);
	}
	if (!local) {
		local = &local_sub;
		local = &__$true;
	}
	if (!filter_param) {
		filter = 1;
	} else {
		filter = zephir_get_boolval(filter_param);
	}
	if (!attributes) {
		attributes = &attributes_sub;
		attributes = &__$null;
	}
	if (!version_param) {
		ZEPHIR_INIT_VAR(&version);
		ZVAL_STRING(&version, "");
	} else {
		zephir_get_strval(&version, version_param);
	}
	if (!autoVersion_param) {
		autoVersion = 0;
	} else {
		autoVersion = zephir_get_boolval(autoVersion_param);
	}


	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, phalcon_assets_asset_js_ce);
	if (filter) {
		ZVAL_BOOL(&_1, 1);
	} else {
		ZVAL_BOOL(&_1, 0);
	}
	if (autoVersion) {
		ZVAL_BOOL(&_2, 1);
	} else {
		ZVAL_BOOL(&_2, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 130, &path, local, &_1, attributes, &version, &_2);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "js");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addassetbytype", NULL, 0, &_3, &_0);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Creates/Returns a collection of assets
 */
PHP_METHOD(Phalcon_Assets_Manager, collection) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, collection, _0;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(&name, name_param);


	ZEPHIR_OBS_VAR(&collection);
	zephir_read_property(&_0, this_ptr, SL("collections"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&collection, &_0, &name, 0 TSRMLS_CC))) {
		ZEPHIR_INIT_NVAR(&collection);
		object_init_ex(&collection, phalcon_assets_collection_ce);
		ZEPHIR_CALL_METHOD(NULL, &collection, "__construct", NULL, 131);
		zephir_check_call_status();
		zephir_update_property_array(this_ptr, SL("collections"), &name, &collection TSRMLS_CC);
	}
	RETURN_CCTOR(&collection);

}

/**
 * Creates/Returns a collection of assets by type
 */
PHP_METHOD(Phalcon_Assets_Manager, collectionAssetsByType) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval type;
	zval *assets_param = NULL, *type_param = NULL, asset, *_0, _1$$3;
	zval assets, filtered;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&assets);
	ZVAL_UNDEF(&filtered);
	ZVAL_UNDEF(&asset);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&type);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &assets_param, &type_param);

	zephir_get_arrval(&assets, assets_param);
	zephir_get_strval(&type, type_param);


	ZEPHIR_INIT_VAR(&filtered);
	array_init(&filtered);
	zephir_is_iterable(&assets, 0, "phalcon/Assets/Manager.zep", 241);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&assets), _0)
	{
		ZEPHIR_INIT_NVAR(&asset);
		ZVAL_COPY(&asset, _0);
		ZEPHIR_CALL_METHOD(&_1$$3, &asset, "gettype", NULL, 0);
		zephir_check_call_status();
		if (ZEPHIR_IS_EQUAL(&_1$$3, &type)) {
			zephir_array_append(&filtered, &asset, PH_SEPARATE, "phalcon/Assets/Manager.zep", 237);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&asset);
	RETURN_CTOR(&filtered);

}

/**
 * Returns true or false if collection exists.
 *
 * <code>
 * if ($assets->exists("jsHeader")) {
 *     // \Phalcon\Assets\Collection
 *     $collection = $assets->get("jsHeader");
 * }
 * </code>
 */
PHP_METHOD(Phalcon_Assets_Manager, exists) {

	zval *id_param = NULL, _0;
	zval id;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&id);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &id_param);

	if (UNEXPECTED(Z_TYPE_P(id_param) != IS_STRING && Z_TYPE_P(id_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'id' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(id_param) == IS_STRING)) {
		zephir_get_strval(&id, id_param);
	} else {
		ZEPHIR_INIT_VAR(&id);
		ZVAL_EMPTY_STRING(&id);
	}


	zephir_read_property(&_0, this_ptr, SL("collections"), PH_NOISY_CC | PH_READONLY);
	RETURN_MM_BOOL(zephir_array_isset(&_0, &id));

}

/**
 * Returns a collection by its id.
 *
 * <code>
 * $scripts = $assets->get("js");
 * </code>
 */
PHP_METHOD(Phalcon_Assets_Manager, get) {

	zval *id_param = NULL, collection, _0;
	zval id;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&id);
	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &id_param);

	if (UNEXPECTED(Z_TYPE_P(id_param) != IS_STRING && Z_TYPE_P(id_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'id' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(id_param) == IS_STRING)) {
		zephir_get_strval(&id, id_param);
	} else {
		ZEPHIR_INIT_VAR(&id);
		ZVAL_EMPTY_STRING(&id);
	}


	ZEPHIR_OBS_VAR(&collection);
	zephir_read_property(&_0, this_ptr, SL("collections"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!(zephir_array_isset_fetch(&collection, &_0, &id, 0 TSRMLS_CC)))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_assets_exception_ce, "The collection does not exist in the manager", "phalcon/Assets/Manager.zep", 271);
		return;
	}
	RETURN_CCTOR(&collection);

}

/**
 * Returns existing collections in the manager
 */
PHP_METHOD(Phalcon_Assets_Manager, getCollections) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "collections");

}

/**
 * Returns the CSS collection of assets
 */
PHP_METHOD(Phalcon_Assets_Manager, getCss) {

	zval collection, _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("collections"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_string_fetch(&collection, &_0, SL("css"), 1))) {
		object_init_ex(return_value, phalcon_assets_collection_ce);
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 131);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_CTOR(&collection);

}

/**
 * Returns the internal dependency injector
 */
PHP_METHOD(Phalcon_Assets_Manager, getDI) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "container");

}

/**
 * Returns the CSS collection of assets
 */
PHP_METHOD(Phalcon_Assets_Manager, getJs) {

	zval collection, _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("collections"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_string_fetch(&collection, &_0, SL("js"), 1))) {
		object_init_ex(return_value, phalcon_assets_collection_ce);
		ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 131);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_CTOR(&collection);

}

/**
 * Returns the manager options
 */
PHP_METHOD(Phalcon_Assets_Manager, getOptions) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "options");

}

/**
 * Traverses a collection calling the callback to generate its HTML
 *
 * @param callback callback
 * @param string type
 */
PHP_METHOD(Phalcon_Assets_Manager, output) {

	zend_bool filterNeeded = 0, _17$$23, _21$$24, _28$$42, _30$$43, _34$$51;
	zval output;
	zephir_fcall_cache_entry *_15 = NULL, *_19 = NULL, *_20 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *collection, collection_sub, *callback, callback_sub, *type = NULL, type_sub, asset, assets, attributes, autoVersion, collectionSourcePath, collectionTargetPath, completeSourcePath, completeTargetPath, content, filter, filters, filteredContent, filteredJoinedContent, html, join, local, modificationTime, mustFilter, options, parameters, path, prefixedPath, sourceBasePath, sourcePath, targetBasePath, targetPath, targetUri, typeCss, useImplicitOutput, version, _0, *_7, _1$$3, _2$$10, _3$$10, _4$$9, _5$$11, _6$$11, _8$$15, _9$$15, _10$$17, _11$$17, _12$$19, _13$$19, _14$$20, _16$$23, _18$$23, _22$$25, _23$$25, _24$$26, *_25$$32, _26$$37, _27$$42, _29$$42, _31$$44, _32$$44, _33$$45, _35$$52, _36$$53;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&collection_sub);
	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&type_sub);
	ZVAL_UNDEF(&asset);
	ZVAL_UNDEF(&assets);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&autoVersion);
	ZVAL_UNDEF(&collectionSourcePath);
	ZVAL_UNDEF(&collectionTargetPath);
	ZVAL_UNDEF(&completeSourcePath);
	ZVAL_UNDEF(&completeTargetPath);
	ZVAL_UNDEF(&content);
	ZVAL_UNDEF(&filter);
	ZVAL_UNDEF(&filters);
	ZVAL_UNDEF(&filteredContent);
	ZVAL_UNDEF(&filteredJoinedContent);
	ZVAL_UNDEF(&html);
	ZVAL_UNDEF(&join);
	ZVAL_UNDEF(&local);
	ZVAL_UNDEF(&modificationTime);
	ZVAL_UNDEF(&mustFilter);
	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&parameters);
	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&prefixedPath);
	ZVAL_UNDEF(&sourceBasePath);
	ZVAL_UNDEF(&sourcePath);
	ZVAL_UNDEF(&targetBasePath);
	ZVAL_UNDEF(&targetPath);
	ZVAL_UNDEF(&targetUri);
	ZVAL_UNDEF(&typeCss);
	ZVAL_UNDEF(&useImplicitOutput);
	ZVAL_UNDEF(&version);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$10);
	ZVAL_UNDEF(&_3$$10);
	ZVAL_UNDEF(&_4$$9);
	ZVAL_UNDEF(&_5$$11);
	ZVAL_UNDEF(&_6$$11);
	ZVAL_UNDEF(&_8$$15);
	ZVAL_UNDEF(&_9$$15);
	ZVAL_UNDEF(&_10$$17);
	ZVAL_UNDEF(&_11$$17);
	ZVAL_UNDEF(&_12$$19);
	ZVAL_UNDEF(&_13$$19);
	ZVAL_UNDEF(&_14$$20);
	ZVAL_UNDEF(&_16$$23);
	ZVAL_UNDEF(&_18$$23);
	ZVAL_UNDEF(&_22$$25);
	ZVAL_UNDEF(&_23$$25);
	ZVAL_UNDEF(&_24$$26);
	ZVAL_UNDEF(&_26$$37);
	ZVAL_UNDEF(&_27$$42);
	ZVAL_UNDEF(&_29$$42);
	ZVAL_UNDEF(&_31$$44);
	ZVAL_UNDEF(&_32$$44);
	ZVAL_UNDEF(&_33$$45);
	ZVAL_UNDEF(&_35$$52);
	ZVAL_UNDEF(&_36$$53);
	ZVAL_UNDEF(&output);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &collection, &callback, &type);

	ZEPHIR_SEPARATE_PARAM(type);


	ZEPHIR_INIT_VAR(&sourceBasePath);
	ZVAL_NULL(&sourceBasePath);
	ZEPHIR_INIT_VAR(&targetBasePath);
	ZVAL_NULL(&targetBasePath);
	ZEPHIR_OBS_VAR(&useImplicitOutput);
	zephir_read_property(&useImplicitOutput, this_ptr, SL("implicitOutput"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(&output);
	ZVAL_STRING(&output, "");
	ZEPHIR_CALL_METHOD(&_0, collection, "getassets", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&assets, this_ptr, "collectionassetsbytype", NULL, 0, &_0, type);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&filters, collection, "getfilters", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&typeCss);
	ZVAL_STRING(&typeCss, "css");
	if (zephir_fast_count_int(&filters TSRMLS_CC)) {
		zephir_read_property(&_1$$3, this_ptr, SL("options"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&options, &_1$$3);
		if (Z_TYPE_P(&options) == IS_ARRAY) {
			ZEPHIR_OBS_NVAR(&sourceBasePath);
			zephir_array_isset_string_fetch(&sourceBasePath, &options, SL("sourceBasePath"), 0);
			ZEPHIR_OBS_NVAR(&targetBasePath);
			zephir_array_isset_string_fetch(&targetBasePath, &options, SL("targetBasePath"), 0);
		}
		ZEPHIR_CALL_METHOD(&collectionSourcePath, collection, "getsourcepath", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(&collectionSourcePath)) {
			ZEPHIR_INIT_VAR(&completeSourcePath);
			ZEPHIR_CONCAT_VV(&completeSourcePath, &sourceBasePath, &collectionSourcePath);
		} else {
			ZEPHIR_CPY_WRT(&completeSourcePath, &sourceBasePath);
		}
		ZEPHIR_CALL_METHOD(&collectionTargetPath, collection, "gettargetpath", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(&collectionTargetPath)) {
			ZEPHIR_INIT_VAR(&completeTargetPath);
			ZEPHIR_CONCAT_VV(&completeTargetPath, &targetBasePath, &collectionTargetPath);
		} else {
			ZEPHIR_CPY_WRT(&completeTargetPath, &targetBasePath);
		}
		ZEPHIR_INIT_VAR(&filteredJoinedContent);
		ZVAL_STRING(&filteredJoinedContent, "");
		ZEPHIR_CALL_METHOD(&join, collection, "getjoin", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(&join)) {
			if (UNEXPECTED(!zephir_is_true(&completeTargetPath))) {
				ZEPHIR_INIT_VAR(&_2$$10);
				object_init_ex(&_2$$10, phalcon_assets_exception_ce);
				ZEPHIR_INIT_VAR(&_3$$10);
				ZEPHIR_CONCAT_SVS(&_3$$10, "Path '", &completeTargetPath, "' is not a valid target path (1)");
				ZEPHIR_CALL_METHOD(NULL, &_2$$10, "__construct", NULL, 1, &_3$$10);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_2$$10, "phalcon/Assets/Manager.zep", 444 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_FUNCTION(&_4$$9, "is_dir", NULL, 98, &completeTargetPath);
			zephir_check_call_status();
			if (UNEXPECTED(zephir_is_true(&_4$$9))) {
				ZEPHIR_INIT_VAR(&_5$$11);
				object_init_ex(&_5$$11, phalcon_assets_exception_ce);
				ZEPHIR_INIT_VAR(&_6$$11);
				ZEPHIR_CONCAT_SVS(&_6$$11, "Path '", &completeTargetPath, "' is not a valid target path (2), is dir.");
				ZEPHIR_CALL_METHOD(NULL, &_5$$11, "__construct", NULL, 1, &_6$$11);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_5$$11, "phalcon/Assets/Manager.zep", 450 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	zephir_is_iterable(&assets, 0, "phalcon/Assets/Manager.zep", 719);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&assets), _7)
	{
		ZEPHIR_INIT_NVAR(&asset);
		ZVAL_COPY(&asset, _7);
		filterNeeded = 0;
		ZEPHIR_CALL_METHOD(type, &asset, "gettype", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&local, &asset, "getlocal", NULL, 0);
		zephir_check_call_status();
		if (zephir_fast_count_int(&filters TSRMLS_CC)) {
			if (zephir_is_true(&local)) {
				ZEPHIR_CALL_METHOD(&sourcePath, &asset, "getrealsourcepath", NULL, 0, &completeSourcePath);
				zephir_check_call_status();
				if (UNEXPECTED(!zephir_is_true(&sourcePath))) {
					ZEPHIR_CALL_METHOD(&sourcePath, &asset, "getpath", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_8$$15);
					object_init_ex(&_8$$15, phalcon_assets_exception_ce);
					ZEPHIR_INIT_LNVAR(_9$$15);
					ZEPHIR_CONCAT_SVS(&_9$$15, "Asset '", &sourcePath, "' does not have a valid source path");
					ZEPHIR_CALL_METHOD(NULL, &_8$$15, "__construct", NULL, 1, &_9$$15);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_8$$15, "phalcon/Assets/Manager.zep", 490 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CALL_METHOD(&sourcePath, &asset, "getpath", NULL, 0);
				zephir_check_call_status();
				filterNeeded = 1;
			}
			ZEPHIR_CALL_METHOD(&targetPath, &asset, "getrealtargetpath", NULL, 0, &completeTargetPath);
			zephir_check_call_status();
			if (UNEXPECTED(!zephir_is_true(&targetPath))) {
				ZEPHIR_INIT_NVAR(&_10$$17);
				object_init_ex(&_10$$17, phalcon_assets_exception_ce);
				ZEPHIR_INIT_LNVAR(_11$$17);
				ZEPHIR_CONCAT_SVS(&_11$$17, "Asset '", &sourcePath, "' does not have a valid target path");
				ZEPHIR_CALL_METHOD(NULL, &_10$$17, "__construct", NULL, 1, &_11$$17);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_10$$17, "phalcon/Assets/Manager.zep", 517 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (zephir_is_true(&local)) {
				if (UNEXPECTED(ZEPHIR_IS_EQUAL(&targetPath, &sourcePath))) {
					ZEPHIR_INIT_NVAR(&_12$$19);
					object_init_ex(&_12$$19, phalcon_assets_exception_ce);
					ZEPHIR_INIT_LNVAR(_13$$19);
					ZEPHIR_CONCAT_SVS(&_13$$19, "Asset '", &targetPath, "' have the same source and target paths");
					ZEPHIR_CALL_METHOD(NULL, &_12$$19, "__construct", NULL, 1, &_13$$19);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_12$$19, "phalcon/Assets/Manager.zep", 528 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
				if ((zephir_file_exists(&targetPath TSRMLS_CC) == SUCCESS)) {
					ZEPHIR_INIT_NVAR(&_14$$20);
					if (zephir_compare_mtime(&targetPath, &sourcePath TSRMLS_CC)) {
						filterNeeded = 1;
					}
				} else {
					filterNeeded = 1;
				}
			}
		} else {
			ZEPHIR_CALL_METHOD(&path, &asset, "getrealtargeturi", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&prefixedPath, this_ptr, "getprefixedpath", &_15, 134, collection, &path);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_16$$23, &asset, "getversion", NULL, 0);
			zephir_check_call_status();
			_17$$23 = Z_TYPE_P(&_16$$23) == IS_NULL;
			if (_17$$23) {
				ZEPHIR_CALL_METHOD(&_18$$23, &asset, "isautoversion", NULL, 0);
				zephir_check_call_status();
				_17$$23 = zephir_is_true(&_18$$23);
			}
			if (_17$$23) {
				ZEPHIR_CALL_METHOD(&version, collection, "getversion", &_19, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&autoVersion, collection, "isautoversion", &_20, 0);
				zephir_check_call_status();
				_21$$24 = zephir_is_true(&autoVersion);
				if (_21$$24) {
					_21$$24 = zephir_is_true(&local);
				}
				if (_21$$24) {
					ZEPHIR_CALL_METHOD(&_22$$25, &asset, "getrealsourcepath", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&modificationTime);
					zephir_filemtime(&modificationTime, &_22$$25 TSRMLS_CC);
					ZEPHIR_INIT_LNVAR(_23$$25);
					if (zephir_is_true(&version)) {
						ZEPHIR_INIT_NVAR(&_23$$25);
						ZEPHIR_CONCAT_VSV(&_23$$25, &version, ".", &modificationTime);
					} else {
						ZEPHIR_CPY_WRT(&_23$$25, &modificationTime);
					}
					ZEPHIR_CPY_WRT(&version, &_23$$25);
				}
				if (zephir_is_true(&version)) {
					ZEPHIR_INIT_LNVAR(_24$$26);
					ZEPHIR_CONCAT_VSV(&_24$$26, &prefixedPath, "?ver=", &version);
					ZEPHIR_CPY_WRT(&prefixedPath, &_24$$26);
				}
			}
			ZEPHIR_CALL_METHOD(&attributes, &asset, "getattributes", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&parameters);
			array_init(&parameters);
			if (Z_TYPE_P(&attributes) == IS_ARRAY) {
				zephir_array_update_long(&attributes, 0, &prefixedPath, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				zephir_array_append(&parameters, &attributes, PH_SEPARATE, "phalcon/Assets/Manager.zep", 572);
			} else {
				zephir_array_append(&parameters, &prefixedPath, PH_SEPARATE, "phalcon/Assets/Manager.zep", 574);
			}
			zephir_array_append(&parameters, &local, PH_SEPARATE, "phalcon/Assets/Manager.zep", 576);
			ZEPHIR_INIT_NVAR(&html);
			ZEPHIR_CALL_USER_FUNC_ARRAY(&html, callback, &parameters);
			zephir_check_call_status();
			if (ZEPHIR_IS_TRUE(&useImplicitOutput)) {
				zend_print_zval(&html, 0);
			} else {
				zephir_concat_self(&output, &html TSRMLS_CC);
			}
			continue;
		}
		if (filterNeeded == 1) {
			ZEPHIR_CALL_METHOD(&content, &asset, "getcontent", NULL, 0, &completeSourcePath);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&mustFilter, &asset, "getfilter", NULL, 0);
			zephir_check_call_status();
			if (ZEPHIR_IS_TRUE(&mustFilter)) {
				zephir_is_iterable(&filters, 0, "phalcon/Assets/Manager.zep", 630);
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&filters), _25$$32)
				{
					ZEPHIR_INIT_NVAR(&filter);
					ZVAL_COPY(&filter, _25$$32);
					if (UNEXPECTED(Z_TYPE_P(&filter) != IS_OBJECT)) {
						ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_assets_exception_ce, "Filter is invalid", "phalcon/Assets/Manager.zep", 617);
						return;
					}
					ZEPHIR_CALL_METHOD(&filteredContent, &filter, "filter", NULL, 0, &content);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&content, &filteredContent);
				} ZEND_HASH_FOREACH_END();
				ZEPHIR_INIT_NVAR(&filter);
				if (ZEPHIR_IS_TRUE(&join)) {
					if (ZEPHIR_IS_EQUAL(type, &typeCss)) {
						zephir_concat_self(&filteredJoinedContent, &filteredContent TSRMLS_CC);
					} else {
						ZEPHIR_INIT_LNVAR(_26$$37);
						ZEPHIR_CONCAT_VS(&_26$$37, &filteredContent, ";");
						zephir_concat_self(&filteredJoinedContent, &_26$$37 TSRMLS_CC);
					}
				}
			} else {
				if (ZEPHIR_IS_TRUE(&join)) {
					zephir_concat_self(&filteredJoinedContent, &content TSRMLS_CC);
				} else {
					ZEPHIR_CPY_WRT(&filteredContent, &content);
				}
			}
			if (!(zephir_is_true(&join))) {
				zephir_file_put_contents(NULL, &targetPath, &filteredContent TSRMLS_CC);
			}
		}
		if (!(zephir_is_true(&join))) {
			ZEPHIR_CALL_METHOD(&path, &asset, "getrealtargeturi", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&prefixedPath, this_ptr, "getprefixedpath", &_15, 134, collection, &path);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_27$$42, &asset, "getversion", NULL, 0);
			zephir_check_call_status();
			_28$$42 = Z_TYPE_P(&_27$$42) == IS_NULL;
			if (_28$$42) {
				ZEPHIR_CALL_METHOD(&_29$$42, &asset, "isautoversion", NULL, 0);
				zephir_check_call_status();
				_28$$42 = zephir_is_true(&_29$$42);
			}
			if (_28$$42) {
				ZEPHIR_CALL_METHOD(&version, collection, "getversion", &_19, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&autoVersion, collection, "isautoversion", &_20, 0);
				zephir_check_call_status();
				_30$$43 = zephir_is_true(&autoVersion);
				if (_30$$43) {
					_30$$43 = zephir_is_true(&local);
				}
				if (_30$$43) {
					ZEPHIR_CALL_METHOD(&_31$$44, &asset, "getrealsourcepath", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&modificationTime);
					zephir_filemtime(&modificationTime, &_31$$44 TSRMLS_CC);
					ZEPHIR_INIT_LNVAR(_32$$44);
					if (zephir_is_true(&version)) {
						ZEPHIR_INIT_NVAR(&_32$$44);
						ZEPHIR_CONCAT_VSV(&_32$$44, &version, ".", &modificationTime);
					} else {
						ZEPHIR_CPY_WRT(&_32$$44, &modificationTime);
					}
					ZEPHIR_CPY_WRT(&version, &_32$$44);
				}
				if (zephir_is_true(&version)) {
					ZEPHIR_INIT_LNVAR(_33$$45);
					ZEPHIR_CONCAT_VSV(&_33$$45, &prefixedPath, "?ver=", &version);
					ZEPHIR_CPY_WRT(&prefixedPath, &_33$$45);
				}
			}
			ZEPHIR_CALL_METHOD(&attributes, &asset, "getattributes", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&local);
			ZVAL_BOOL(&local, 1);
			ZEPHIR_INIT_NVAR(&parameters);
			array_init(&parameters);
			if (Z_TYPE_P(&attributes) == IS_ARRAY) {
				zephir_array_update_long(&attributes, 0, &prefixedPath, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				zephir_array_append(&parameters, &attributes, PH_SEPARATE, "phalcon/Assets/Manager.zep", 697);
			} else {
				zephir_array_append(&parameters, &prefixedPath, PH_SEPARATE, "phalcon/Assets/Manager.zep", 699);
			}
			zephir_array_append(&parameters, &local, PH_SEPARATE, "phalcon/Assets/Manager.zep", 701);
			ZEPHIR_INIT_NVAR(&html);
			ZEPHIR_CALL_USER_FUNC_ARRAY(&html, callback, &parameters);
			zephir_check_call_status();
			if (ZEPHIR_IS_TRUE(&useImplicitOutput)) {
				zend_print_zval(&html, 0);
			} else {
				zephir_concat_self(&output, &html TSRMLS_CC);
			}
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&asset);
	if (zephir_fast_count_int(&filters TSRMLS_CC)) {
		if (ZEPHIR_IS_TRUE(&join)) {
			zephir_file_put_contents(NULL, &completeTargetPath, &filteredJoinedContent TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&targetUri, collection, "gettargeturi", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&prefixedPath, this_ptr, "getprefixedpath", &_15, 134, collection, &targetUri);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&version, collection, "getversion", &_19, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&autoVersion, collection, "isautoversion", &_20, 0);
			zephir_check_call_status();
			_34$$51 = zephir_is_true(&autoVersion);
			if (_34$$51) {
				_34$$51 = zephir_is_true(&local);
			}
			if (_34$$51) {
				ZEPHIR_INIT_NVAR(&modificationTime);
				zephir_filemtime(&modificationTime, &completeTargetPath TSRMLS_CC);
				ZEPHIR_INIT_VAR(&_35$$52);
				if (zephir_is_true(&version)) {
					ZEPHIR_INIT_NVAR(&_35$$52);
					ZEPHIR_CONCAT_VSV(&_35$$52, &version, ".", &modificationTime);
				} else {
					ZEPHIR_CPY_WRT(&_35$$52, &modificationTime);
				}
				ZEPHIR_CPY_WRT(&version, &_35$$52);
			}
			if (zephir_is_true(&version)) {
				ZEPHIR_INIT_VAR(&_36$$53);
				ZEPHIR_CONCAT_VSV(&_36$$53, &prefixedPath, "?ver=", &version);
				ZEPHIR_CPY_WRT(&prefixedPath, &_36$$53);
			}
			ZEPHIR_CALL_METHOD(&attributes, collection, "getattributes", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&local, collection, "gettargetlocal", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&parameters);
			array_init(&parameters);
			if (Z_TYPE_P(&attributes) == IS_ARRAY) {
				zephir_array_update_long(&attributes, 0, &prefixedPath, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				zephir_array_append(&parameters, &attributes, PH_SEPARATE, "phalcon/Assets/Manager.zep", 762);
			} else {
				zephir_array_append(&parameters, &prefixedPath, PH_SEPARATE, "phalcon/Assets/Manager.zep", 764);
			}
			zephir_array_append(&parameters, &local, PH_SEPARATE, "phalcon/Assets/Manager.zep", 766);
			ZEPHIR_INIT_NVAR(&html);
			ZEPHIR_CALL_USER_FUNC_ARRAY(&html, callback, &parameters);
			zephir_check_call_status();
			if (ZEPHIR_IS_TRUE(&useImplicitOutput)) {
				zend_print_zval(&html, 0);
			} else {
				zephir_concat_self(&output, &html TSRMLS_CC);
			}
		}
	}
	RETURN_CTOR(&output);

}

/**
 * Prints the HTML for CSS assets
 */
PHP_METHOD(Phalcon_Assets_Manager, outputCss) {

	zend_bool _2;
	zval callback;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *collectionName_param = NULL, collection, container, tag, _0, _1, _3, _4$$5;
	zval collectionName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&collectionName);
	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&tag);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&callback);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &collectionName_param);

	if (!collectionName_param) {
		ZEPHIR_INIT_VAR(&collectionName);
		ZVAL_STRING(&collectionName, "");
	} else {
		zephir_get_strval(&collectionName, collectionName_param);
	}


	if (!(!(Z_TYPE_P(&collectionName) == IS_UNDEF) && Z_STRLEN_P(&collectionName))) {
		ZEPHIR_CALL_METHOD(&collection, this_ptr, "getcss", NULL, 0);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(&collection, this_ptr, "get", NULL, 0, &collectionName);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&callback);
	zephir_create_array(&callback, 2, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Phalcon\\Tag");
	zephir_array_fast_append(&callback, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "stylesheetLink");
	zephir_array_fast_append(&callback, &_0);
	zephir_read_property(&_1, this_ptr, SL("container"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&container, &_1);
	_2 = Z_TYPE_P(&container) == IS_OBJECT;
	if (_2) {
		ZEPHIR_INIT_NVAR(&_0);
		ZVAL_STRING(&_0, "tag");
		ZEPHIR_CALL_METHOD(&_3, &container, "has", NULL, 0, &_0);
		zephir_check_call_status();
		_2 = zephir_is_true(&_3);
	}
	if (_2) {
		ZEPHIR_INIT_VAR(&_4$$5);
		ZVAL_STRING(&_4$$5, "tag");
		ZEPHIR_CALL_METHOD(&tag, &container, "getshared", NULL, 0, &_4$$5);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&callback);
		zephir_create_array(&callback, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&callback, &tag);
		ZEPHIR_INIT_NVAR(&_4$$5);
		ZVAL_STRING(&_4$$5, "stylesheetLink");
		zephir_array_fast_append(&callback, &_4$$5);
	}
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "css");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "output", NULL, 0, &collection, &callback, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Traverses a collection and generate its HTML
 *
 * @param string type
 */
PHP_METHOD(Phalcon_Assets_Manager, outputInline) {

	zval html, joinedContent, output;
	zephir_fcall_cache_entry *_4 = NULL, *_8 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *collection, collection_sub, *type, type_sub, attributes, code, codes, content, filter, filters, join, *_0$$3, _15$$3, *_1$$4, _2$$5, _3$$8, _5$$8, _6$$8, _7$$8, _9$$8, _10$$9, _11$$9, _12$$9, _13$$9, _14$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&collection_sub);
	ZVAL_UNDEF(&type_sub);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&code);
	ZVAL_UNDEF(&codes);
	ZVAL_UNDEF(&content);
	ZVAL_UNDEF(&filter);
	ZVAL_UNDEF(&filters);
	ZVAL_UNDEF(&join);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$8);
	ZVAL_UNDEF(&_5$$8);
	ZVAL_UNDEF(&_6$$8);
	ZVAL_UNDEF(&_7$$8);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&html);
	ZVAL_UNDEF(&joinedContent);
	ZVAL_UNDEF(&output);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &collection, &type);



	ZEPHIR_INIT_VAR(&output);
	ZVAL_STRING(&output, "");
	ZEPHIR_INIT_VAR(&html);
	ZVAL_STRING(&html, "");
	ZEPHIR_INIT_VAR(&joinedContent);
	ZVAL_STRING(&joinedContent, "");
	ZEPHIR_CALL_METHOD(&codes, collection, "getcodes", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&filters, collection, "getfilters", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&join, collection, "getjoin", NULL, 0);
	zephir_check_call_status();
	if (zephir_fast_count_int(&codes TSRMLS_CC)) {
		zephir_is_iterable(&codes, 0, "phalcon/Assets/Manager.zep", 858);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&codes), _0$$3)
		{
			ZEPHIR_INIT_NVAR(&code);
			ZVAL_COPY(&code, _0$$3);
			ZEPHIR_CALL_METHOD(&attributes, &code, "getattributes", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&content, &code, "getcontent", NULL, 0);
			zephir_check_call_status();
			zephir_is_iterable(&filters, 0, "phalcon/Assets/Manager.zep", 849);
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&filters), _1$$4)
			{
				ZEPHIR_INIT_NVAR(&filter);
				ZVAL_COPY(&filter, _1$$4);
				if (UNEXPECTED(Z_TYPE_P(&filter) != IS_OBJECT)) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_assets_exception_ce, "Filter is invalid", "phalcon/Assets/Manager.zep", 839);
					return;
				}
				ZEPHIR_CALL_METHOD(&_2$$5, &filter, "filter", NULL, 0, &content);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&content, &_2$$5);
			} ZEND_HASH_FOREACH_END();
			ZEPHIR_INIT_NVAR(&filter);
			if (zephir_is_true(&join)) {
				zephir_concat_self(&joinedContent, &content TSRMLS_CC);
			} else {
				ZVAL_BOOL(&_5$$8, 0);
				ZVAL_BOOL(&_6$$8, 1);
				ZEPHIR_CALL_CE_STATIC(&_3$$8, phalcon_tag_ce, "taghtml", &_4, 0, type, &attributes, &_5$$8, &_6$$8);
				zephir_check_call_status();
				ZVAL_BOOL(&_5$$8, 1);
				ZEPHIR_CALL_CE_STATIC(&_7$$8, phalcon_tag_ce, "taghtmlclose", &_8, 0, type, &_5$$8);
				zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_9$$8);
				ZEPHIR_CONCAT_VVV(&_9$$8, &_3$$8, &content, &_7$$8);
				zephir_concat_self(&html, &_9$$8 TSRMLS_CC);
			}
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&code);
		if (zephir_is_true(&join)) {
			ZVAL_BOOL(&_11$$9, 0);
			ZVAL_BOOL(&_12$$9, 1);
			ZEPHIR_CALL_CE_STATIC(&_10$$9, phalcon_tag_ce, "taghtml", &_4, 0, type, &attributes, &_11$$9, &_12$$9);
			zephir_check_call_status();
			ZVAL_BOOL(&_11$$9, 1);
			ZEPHIR_CALL_CE_STATIC(&_13$$9, phalcon_tag_ce, "taghtmlclose", &_8, 0, type, &_11$$9);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_14$$9);
			ZEPHIR_CONCAT_VVV(&_14$$9, &_10$$9, &joinedContent, &_13$$9);
			zephir_concat_self(&html, &_14$$9 TSRMLS_CC);
		}
		zephir_read_property(&_15$$3, this_ptr, SL("implicitOutput"), PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_IS_TRUE(&_15$$3)) {
			zend_print_zval(&html, 0);
		} else {
			zephir_concat_self(&output, &html TSRMLS_CC);
		}
	}
	RETURN_CTOR(&output);

}

/**
 * Prints the HTML for inline CSS
 */
PHP_METHOD(Phalcon_Assets_Manager, outputInlineCss) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *collectionName_param = NULL, collection, _0;
	zval collectionName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&collectionName);
	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &collectionName_param);

	if (!collectionName_param) {
		ZEPHIR_INIT_VAR(&collectionName);
		ZVAL_STRING(&collectionName, "");
	} else {
		zephir_get_strval(&collectionName, collectionName_param);
	}


	if (!(!(Z_TYPE_P(&collectionName) == IS_UNDEF) && Z_STRLEN_P(&collectionName))) {
		ZEPHIR_CALL_METHOD(&collection, this_ptr, "getcss", NULL, 0);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(&collection, this_ptr, "get", NULL, 0, &collectionName);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "style");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "outputinline", NULL, 0, &collection, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Prints the HTML for inline JS
 */
PHP_METHOD(Phalcon_Assets_Manager, outputInlineJs) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *collectionName_param = NULL, collection, _0;
	zval collectionName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&collectionName);
	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &collectionName_param);

	if (!collectionName_param) {
		ZEPHIR_INIT_VAR(&collectionName);
		ZVAL_STRING(&collectionName, "");
	} else {
		zephir_get_strval(&collectionName, collectionName_param);
	}


	if (!(!(Z_TYPE_P(&collectionName) == IS_UNDEF) && Z_STRLEN_P(&collectionName))) {
		ZEPHIR_CALL_METHOD(&collection, this_ptr, "getjs", NULL, 0);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(&collection, this_ptr, "get", NULL, 0, &collectionName);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "script");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "outputinline", NULL, 0, &collection, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Prints the HTML for JS assets
 */
PHP_METHOD(Phalcon_Assets_Manager, outputJs) {

	zend_bool _2;
	zval callback;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *collectionName_param = NULL, collection, container, tag, _0, _1, _3, _4$$5;
	zval collectionName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&collectionName);
	ZVAL_UNDEF(&collection);
	ZVAL_UNDEF(&container);
	ZVAL_UNDEF(&tag);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&callback);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &collectionName_param);

	if (!collectionName_param) {
		ZEPHIR_INIT_VAR(&collectionName);
		ZVAL_STRING(&collectionName, "");
	} else {
		zephir_get_strval(&collectionName, collectionName_param);
	}


	if (!(!(Z_TYPE_P(&collectionName) == IS_UNDEF) && Z_STRLEN_P(&collectionName))) {
		ZEPHIR_CALL_METHOD(&collection, this_ptr, "getjs", NULL, 0);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(&collection, this_ptr, "get", NULL, 0, &collectionName);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&callback);
	zephir_create_array(&callback, 2, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Phalcon\\Tag");
	zephir_array_fast_append(&callback, &_0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "javascriptInclude");
	zephir_array_fast_append(&callback, &_0);
	zephir_read_property(&_1, this_ptr, SL("container"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&container, &_1);
	_2 = Z_TYPE_P(&container) == IS_OBJECT;
	if (_2) {
		ZEPHIR_INIT_NVAR(&_0);
		ZVAL_STRING(&_0, "tag");
		ZEPHIR_CALL_METHOD(&_3, &container, "has", NULL, 0, &_0);
		zephir_check_call_status();
		_2 = zephir_is_true(&_3);
	}
	if (_2) {
		ZEPHIR_INIT_VAR(&_4$$5);
		ZVAL_STRING(&_4$$5, "tag");
		ZEPHIR_CALL_METHOD(&tag, &container, "getshared", NULL, 0, &_4$$5);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&callback);
		zephir_create_array(&callback, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&callback, &tag);
		ZEPHIR_INIT_NVAR(&_4$$5);
		ZVAL_STRING(&_4$$5, "javascriptInclude");
		zephir_array_fast_append(&callback, &_4$$5);
	}
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "js");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "output", NULL, 0, &collection, &callback, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Sets a collection in the Assets Manager
 *
 *<code>
 * $assets->set("js", $collection);
 *</code>
 */
PHP_METHOD(Phalcon_Assets_Manager, set) {

	zval *id_param = NULL, *collection, collection_sub;
	zval id;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&id);
	ZVAL_UNDEF(&collection_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &id_param, &collection);

	if (UNEXPECTED(Z_TYPE_P(id_param) != IS_STRING && Z_TYPE_P(id_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'id' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(id_param) == IS_STRING)) {
		zephir_get_strval(&id, id_param);
	} else {
		ZEPHIR_INIT_VAR(&id);
		ZVAL_EMPTY_STRING(&id);
	}


	zephir_update_property_array(this_ptr, SL("collections"), &id, collection TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Sets the dependency injector
 */
PHP_METHOD(Phalcon_Assets_Manager, setDI) {

	zval *container, container_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);

	zephir_fetch_params(0, 1, 0, &container);



	zephir_update_property_zval(this_ptr, SL("container"), container);

}

/**
 * Sets the manager options
 */
PHP_METHOD(Phalcon_Assets_Manager, setOptions) {

	zval *options_param = NULL;
	zval options;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&options);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &options_param);

	ZEPHIR_OBS_COPY_OR_DUP(&options, options_param);


	zephir_update_property_zval(this_ptr, SL("options"), &options);
	RETURN_THIS();

}

/**
 * Sets if the HTML generated must be directly printed or returned
 */
PHP_METHOD(Phalcon_Assets_Manager, useImplicitOutput) {

	zval *implicitOutput_param = NULL, __$true, __$false;
	zend_bool implicitOutput;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);

	zephir_fetch_params(0, 1, 0, &implicitOutput_param);

	implicitOutput = zephir_get_boolval(implicitOutput_param);


	if (implicitOutput) {
		zephir_update_property_zval(this_ptr, SL("implicitOutput"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("implicitOutput"), &__$false);
	}
	RETURN_THISW();

}

/**
 * Returns the prefixed path
 */
PHP_METHOD(Phalcon_Assets_Manager, getPrefixedPath) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval path;
	zval *collection, collection_sub, *path_param = NULL, prefix;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&collection_sub);
	ZVAL_UNDEF(&prefix);
	ZVAL_UNDEF(&path);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &collection, &path_param);

	zephir_get_strval(&path, path_param);


	ZEPHIR_CALL_METHOD(&prefix, collection, "getprefix", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&prefix)) {
		ZEPHIR_CONCAT_VV(return_value, &prefix, &path);
		RETURN_MM();
	} else {
		RETURN_CTOR(&path);
	}

}

