#include <glib.h>
#include <gio/gio.h>
#include <glib/gprintf.h>

#include "libhal.h"

#define DBUS_PATH_HAL_COMPUTER "/org/freedesktop/Hal/devices/computer"

struct LibHalContext_s {
    DBusConnection *connection;           /**< D-BUS connection */
    dbus_bool_t is_initialized;           /**< Are we initialised */
};

/* Public Interface */

char **
libhal_manager_find_device_string_match(LibHalContext *ctx, const char *key, const char *value, int *num_devices,
                                        DBusError *error)
{
    gchar **default_r_val = {NULL,};
    char **hal_device_names;

    g_return_val_if_fail(ctx, NULL);
    g_return_val_if_fail(key, NULL);
    g_return_val_if_fail(value, NULL);
  
    hal_device_names = g_strdupv(default_r_val);
    *num_devices = 0;
    
    return hal_device_names;
}


void
libhal_free_string_array(char **str_array)
{
    g_strfreev(str_array);
}


LibHalContext *
libhal_ctx_new(void)
{
    LibHalContext *ctx;

    ctx = g_try_malloc0(sizeof(LibHalContext));
    if (ctx == NULL) {
        g_printerr("%s %d : Failed to allocate %lu bytes\n", __FILE__, __LINE__, sizeof(LibHalContext));
        return NULL;
    }

    ctx->is_initialized = FALSE;
    ctx->connection = NULL;

    return ctx;
}


dbus_bool_t
libhal_ctx_set_dbus_connection(LibHalContext *ctx, DBusConnection *conn)
{
    g_return_val_if_fail(ctx, FALSE);
    g_return_val_if_fail(conn, FALSE);
    GError *error = NULL;
    
    ctx->connection = conn;
    
    return TRUE;
}


dbus_bool_t 
libhal_ctx_init(LibHalContext *ctx, DBusError *error)
{
    g_return_val_if_fail(ctx, FALSE);

    if (ctx->connection == NULL)
        return FALSE;

    ctx->is_initialized = TRUE;
    return TRUE;
}


dbus_bool_t    
libhal_ctx_shutdown(LibHalContext *ctx, DBusError *error)
{
    g_return_val_if_fail(ctx, FALSE);

    ctx->is_initialized = FALSE;
    return TRUE;
}


dbus_bool_t    
libhal_ctx_free(LibHalContext *ctx)
{
    g_free(ctx);
    return TRUE;
}


LibHalPropertyType
libhal_device_get_property_type (LibHalContext *ctx, const char *udi, const char *key, DBusError *error)
{
    g_return_val_if_fail(ctx, LIBHAL_PROPERTY_TYPE_INVALID);
    g_return_val_if_fail(key, LIBHAL_PROPERTY_TYPE_INVALID);
    
    int property_type = LIBHAL_PROPERTY_TYPE_INVALID;

    if (g_strcmp0(udi, DBUS_PATH_HAL_COMPUTER) == 0) {
        if (g_strcmp0(key, "system.hardware.serial") == 0)
            property_type = LIBHAL_PROPERTY_TYPE_STRING;
    }
    
    return property_type;
}


char *
libhal_device_get_property_string(LibHalContext *ctx, const char *udi, const char *key, DBusError *error)
{
    g_return_val_if_fail(ctx, NULL);
    g_return_val_if_fail(key, NULL);

    if (g_strcmp0(key, "system.hardware.serial") == 0)
        return dbus_get_local_machine_id();
    else
        return NULL;
}


void
libhal_free_string (char *str)
{
    g_free(str);
    str = NULL;
}


dbus_uint64_t
libhal_device_get_property_uint64 (LibHalContext *ctx, const char *udi, const char *key, DBusError *error)
{
    g_return_val_if_fail(ctx, -1);
    g_return_val_if_fail(key, -1);

    return -1;
}


dbus_int32_t
libhal_device_get_property_int (LibHalContext *ctx, const char *udi, const char *key, DBusError *error)
{
    return -1;
}


double
libhal_device_get_property_double (LibHalContext *ctx, const char *udi, const char *key, DBusError *error)
{
    return -1.0f;
}

