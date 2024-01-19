#include "Settings/AlsRagdollingSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AlsRagdollingSettings)

#if WITH_EDITOR
void FAlsRagdollingSettins::PostEditChangeProperty(const FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName() != GET_MEMBER_NAME_CHECKED(FAlsRagdollingSettins, GroundTraceResponseChannels)) {
		return;
	}

	GroundTraceResponse.SetAllChannels(ECR_Ignore);

	for (const auto CollisionChannel : GroundTraceResponseChannels) {
		GroundTraceResponse.SetResponse(CollisionChannel, ECR_Block);
	}
}
#endif
