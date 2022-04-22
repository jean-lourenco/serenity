/*
 * Copyright (c) 2022, Liav A. <liavalb@hotmail.co.il>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Kernel/FileSystem/SysFS/RootDirectory.h>
#include <Kernel/FileSystem/SysFS/Subsystems/DeviceIdentifiers/BlockDevicesDirectory.h>
#include <Kernel/FileSystem/SysFS/Subsystems/DeviceIdentifiers/CharacterDevicesDirectory.h>
#include <Kernel/FileSystem/SysFS/Subsystems/DeviceIdentifiers/Directory.h>
#include <Kernel/Sections.h>

namespace Kernel {

UNMAP_AFTER_INIT NonnullRefPtr<SysFSDeviceIdentifiersDirectory> SysFSDeviceIdentifiersDirectory::must_create(SysFSRootDirectory const& root_directory)
{
    auto devices_directory = adopt_ref_if_nonnull(new SysFSDeviceIdentifiersDirectory(root_directory)).release_nonnull();
    devices_directory->m_components.append(SysFSBlockDevicesDirectory::must_create(*devices_directory));
    devices_directory->m_components.append(SysFSCharacterDevicesDirectory::must_create(*devices_directory));
    return devices_directory;
}
SysFSDeviceIdentifiersDirectory::SysFSDeviceIdentifiersDirectory(SysFSRootDirectory const& root_directory)
    : SysFSDirectory(root_directory)
{
}

}