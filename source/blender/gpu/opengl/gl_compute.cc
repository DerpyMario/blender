/* SPDX-FileCopyrightText: 2023 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup gpu
 */

#include "gl_compute.hh"

#include "BLI_assert.hh"

#include "gl_debug.hh"

#include "gpu_capabilities_private.hh"

namespace blender::gpu {

void GLCompute::dispatch(int group_x_len, int group_y_len, int group_z_len)
{
  GL_CHECK_RESOURCES("Compute");

  if (!GCaps.compute_shader_support) {
    /* No compute shader can have been compiled on the legacy OpenGL 3.3 code-path, so reaching
     * here means a caller skipped its #GPU_compute_shader_support check. */
    BLI_assert_unreachable();
    return;
  }

  /* Sometime we reference a dispatch size but we want to skip it by setting one dimension to 0.
   * Avoid error being reported on some implementation for these case. */
  if (group_x_len == 0 || group_y_len == 0 || group_z_len == 0) {
    return;
  }

  glDispatchCompute(group_x_len, group_y_len, group_z_len);
}

}  // namespace blender::gpu
