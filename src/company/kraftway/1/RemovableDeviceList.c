#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DevicePathLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ShellLib.h>
#include <Library/ShellCEntryLib.h>

/*
 * Main entry point
 */
INTN
EFIAPI
ShellAppMain (
  IN UINTN Argc,
  IN CHAR16 **Argv
  )
{
  EFI_STATUS Status;
  EFI_HANDLE *Handles;
  UINTN NoHandles;
  UINTN NrRemovableDevices = 0;
  UINTN Idx;

  Status = gBS->LocateHandleBuffer (ByProtocol, &gEfiBlockIoProtocolGuid, NULL, &NoHandles, &Handles);
  if (EFI_ERROR (Status)) {
    Print(L"LocateHandleBuffer failed: %d\n", Status);
    return Status;
  }

  Print(L"Block devices found: %d\n", NoHandles);

  ASSERT (NoHandles > 0);

  for (Idx = 0; Idx < NoHandles; ++Idx) {
    EFI_DEVICE_PATH_PROTOCOL *DevicePath = DevicePathFromHandle(Handles[Idx]);

    while (!IsDevicePathEndType(DevicePath)) {
      if (DevicePathType(DevicePath) == MESSAGING_DEVICE_PATH) {
        /* NOTE: research USB device only
         *
         * Spec:
         * "So, the whole device path for this USB Controller consists:
         * - an ACPI Device Path Node;
         * - a PCI Device Path Node;
         * - a USB Device Path Node;
         * - and a Device Path End Structure."
         *
         * Lets assume that usb hub consists of 3 parts and device consists of 4 parts:
         * - root hub: PciRoot(0)/PCI(31,2)/USB(0,0);
         * - device  : PciRoot(0)/PCI(31,2)/USB(1,0)/<any path ("HD..." on my vm)>.
         */
        if (DevicePathSubType(DevicePath) == MSG_USB_DP) {
          /* this can be a USB hub, check the next path part */
          if (!IsDevicePathEndType(NextDevicePathNode(DevicePath))){
            CHAR16 *DevicePathText = ConvertDevicePathToText(DevicePath, FALSE, FALSE);
            Print(L"%d: %s\n", ++NrRemovableDevices, DevicePathText);
            FreePool(DevicePathText);
          }
          break;
        }
      }
      DevicePath = NextDevicePathNode(DevicePath);
    }
  }

  gBS->FreePool (Handles);

  Print(L"Removable devices found: %d\n", NrRemovableDevices);

  return Status;
}
