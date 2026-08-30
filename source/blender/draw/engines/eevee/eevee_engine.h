/* SPDX-FileCopyrightText: 2016 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup DNA
 */

#pragma once

#include "DRW_render.hh"
#include "RE_engine.h"

namespace blender {

extern RenderEngineType DRW_engine_viewport_eevee_type;

namespace eevee {

struct Engine : public DrawEngine::Pointer {
  DrawEngine *create_instance() final;

  static void free_static();
};

/**
 * Whether EEVEE can run on the active GPU backend.
 *
 * The engine is built on compute shaders and shader storage buffers, so it is unavailable on the
 * GPU module's legacy OpenGL 3.3 code-path. Callers must check this before selecting the engine;
 * the viewport falls back to Workbench and rendering reports an error.
 */
bool is_supported();

}  // namespace eevee
}  // namespace blender
