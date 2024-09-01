#include "Drop_Widget.h"
#include "Slot_Widget.h"
#include "Slot_DragDropOperation.h"

bool UDrop_Widget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, class UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	USlot_DragDropOperation* Operation = Cast<USlot_DragDropOperation>(InOperation);
	if (Operation->widgetRef != this)
	{
		USlot_Widget* NewSlot = Cast<USlot_Widget>(Operation->widgetRef);
		NewSlot->SpawnItem(); // 아이템 생성
	}
	Operation->widgetRef->SetVisibility(ESlateVisibility::Visible);
	return false;
}
