// Fill out your copyright notice in the Description page of Project Settings.


#include "PPServerRowWidget.h"
#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


void UPPServerRowWidget::Setup(UMainMenu* InParent, uint32 const InIndex)
{
	Parent = InParent;
	Index = InIndex;
	if (!ensure(m_RowButton))
	{
		return;
	}

	m_RowButton->OnClicked.AddDynamic(this, &UPPServerRowWidget::OnRowClicked);
}

void UPPServerRowWidget::SetServerData(FPPServerDataStruct const& InServerData)
{
	ServerData = InServerData;
	ServerName->SetText(FText::FromString(ServerData.Name));
	HostUser->SetText(FText::FromString(ServerData.HostUsername));
	ConnectionFraction->SetText(
		FText::FromString(FString::Printf(TEXT("%d/%d"), ServerData.PlayersAmount, 2)));
}

void UPPServerRowWidget::SetRowIsSelected(bool const InSelected)
{
	bIsSelected = InSelected;
}

void UPPServerRowWidget::OnRowClicked()
{
	Parent->SelectserverRowIndex(Index);
}