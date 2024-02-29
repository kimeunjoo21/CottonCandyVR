// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_Play->OnClicked.AddDynamic(this, &UMenuWidget::OnClickPlay);
	btn_Pause->OnClicked.AddDynamic(this, &UMenuWidget::OnClickPause);
	btn_Key->OnClicked.AddDynamic(this, &UMenuWidget::OnClickKey);
	btn_GoRobby->OnClicked.AddDynamic(this, &UMenuWidget::OnClickGoRobby);
	btn_Quit->OnClicked.AddDynamic(this, &UMenuWidget::OnClickQuit);


}

void UMenuWidget::OnClickPlay()
{
	// �Ͻ������� ������ �ٽ� Play���·� ����
}

void UMenuWidget::OnClickPause()
{
	// Game�� �Ͻ�������
}

void UMenuWidget::OnClickKey()
{
	// ���� Key Image�� �� �տ� ������
}

void UMenuWidget::OnClickGoRobby()
{
	// �� RobbyMaps�� �̵�
	UGameplayStatics::OpenLevel(GetWorld(), "RobbyMaps");
}

void UMenuWidget::OnClickQuit()
{
	// ���� �������� ���� ������Ʈ�� ��������
	UWorld* currentWorld = GetWorld();

	// �� ����
	UKismetSystemLibrary::QuitGame(currentWorld, currentWorld->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
