/*
 *
 *  BlueZ - Bluetooth protocol stack for Linux
 *
 *  Copyright (C) 2014  Google Inc.
 *
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <stdbool.h>
#include <stdint.h>

#include "src/shared/att-types.h"

struct bt_att;

struct bt_att *bt_att_new(int fd);

struct bt_att *bt_att_ref(struct bt_att *att);
void bt_att_unref(struct bt_att *att);

bool bt_att_set_close_on_unref(struct bt_att *att, bool do_close);

typedef void (*bt_att_response_func_t)(uint8_t opcode, const void *pdu,
					uint16_t length, void *user_data);
typedef void (*bt_att_notify_func_t)(uint8_t opcode, const void *pdu,
					uint16_t length, void *user_data);
typedef void (*bt_att_destroy_func_t)(void *user_data);
typedef void (*bt_att_debug_func_t)(const char *str, void *user_data);
typedef void (*bt_att_timeout_func_t)(unsigned int id, uint8_t opcode,
							void *user_data);

bool bt_att_set_debug(struct bt_att *att, bt_att_debug_func_t callback,
				void *user_data, bt_att_destroy_func_t destroy);

uint16_t bt_att_get_mtu(struct bt_att *att);
bool bt_att_set_mtu(struct bt_att *att, uint16_t mtu);

bool bt_att_set_timeout_cb(struct bt_att *att, bt_att_timeout_func_t callback,
						void *user_data,
						bt_att_destroy_func_t destroy);

unsigned int bt_att_send(struct bt_att *att, uint8_t opcode,
					const void *pdu, uint16_t length,
					bt_att_response_func_t callback,
					void *user_data,
					bt_att_destroy_func_t destroy);
bool bt_att_cancel(struct bt_att *att, unsigned int id);
bool bt_att_cancel_all(struct bt_att *att);

unsigned int bt_att_register(struct bt_att *att, uint8_t opcode,
						bt_att_notify_func_t callback,
						void *user_data,
						bt_att_destroy_func_t destroy);
bool bt_att_unregister(struct bt_att *att, unsigned int id);
bool bt_att_unregister_all(struct bt_att *att);
