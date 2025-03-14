#include "AppTask.h"
#include <platform/silabs/BaseApplication.h>

namespace chip {
namespace AppPlatform {

void BaseApplicationDelegate::OnCommissioningSessionStarted()
{
    AppTask::GetAppTask().OnCommissioningStarted();
    isComissioningStarted = true;
}

void BaseApplicationDelegate::OnCommissioningSessionStopped()
{
    AppTask::GetAppTask().OnCommissioningStopped();
    isComissioningStarted = false;
}

} // namespace AppPlatform
} // namespace chip
