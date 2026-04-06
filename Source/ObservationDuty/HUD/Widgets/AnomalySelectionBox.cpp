// 


#include "AnomalySelectionBox.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UAnomalySelectionBox::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnPressed.AddDynamic(this, &UAnomalySelectionBox::OnButtonClicked);
}

void UAnomalySelectionBox::SetupSelectionBox(const FString AnomalyName, EAnomalyType SelectionType)
{
	ButtonText->SetText(FText::FromString(AnomalyName));
	m_SelectionType = SelectionType;
}

void UAnomalySelectionBox::HighlightBox()
{
	Button->SetBackgroundColor(FLinearColor(.03, .03, .03, 1));
}

void UAnomalySelectionBox::UnhighlightBox()
{
	Button->SetBackgroundColor(FLinearColor(.02, .02, .02, 1));
}

void UAnomalySelectionBox::OnButtonClicked()
{
	OnClickedDelegate.ExecuteIfBound(this);
}
