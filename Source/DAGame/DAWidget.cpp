// Fill out your copyright notice in the Description page of Project Settings.

#include "DAWidget.h"
#include "DAButton.h"
#include "DASelectable.h"
#include "WidgetNavigation.h"

void UDAWidget::Accept()
{
	if (CurrentHighlight) {
		IDASelectable* TheInterface = Cast<IDASelectable>(CurrentHighlight);
		if (TheInterface) {
			TheInterface->Execute_OnSelect(CurrentHighlight);
		}
	}
}

void UDAWidget::OnOpen()
{
	bMenuIsOpen = true;
	if (DefaultSelection) {
		SetHighlight(DefaultSelection);
	}
}

void UDAWidget::OnClose()
{
	bMenuIsOpen = false;
}

void UDAWidget::NavigateUp()
{
	if (CurrentHighlight) {
		UWidgetNavigation* Nav = CurrentHighlight->Navigation;
		if (Nav) {
			UWidget *Button = Nav->Up.Widget.Get();
			if (Button) {
				SetHighlight(Button);
			}
		}
	}
}

void UDAWidget::NavigateRight()
{
	if (CurrentHighlight) {
		UWidgetNavigation* Nav = CurrentHighlight->Navigation;
		if (Nav) {
			UWidget *Button = Nav->Right.Widget.Get();
			if (Button) {
				SetHighlight(Button);
			}
		}
	}
}

void UDAWidget::NavigateDown()
{
	if (CurrentHighlight) {
		UWidgetNavigation* Nav = CurrentHighlight->Navigation;
		if (Nav) {
			UWidget *Button = Nav->Down.Widget.Get();
			if (Button) {
				SetHighlight(Button);
			}
		}
	}
}

void UDAWidget::NavigateLeft()
{
	if (CurrentHighlight) {
		UWidgetNavigation* Nav = CurrentHighlight->Navigation;
		if (Nav) {
			UWidget *Button = Nav->Left.Widget.Get();
			if (Button) {
				SetHighlight(Button);
			}
		}
	}
}

void UDAWidget::SetHighlight(UWidget* Widget)
{
	if (CurrentHighlight) {
		IDASelectable* TheInterface = Cast<IDASelectable>(CurrentHighlight);
		if (TheInterface) {
			TheInterface->Execute_UnHighlight(CurrentHighlight);
		}
	}

	CurrentHighlight = Widget;
	IDASelectable* TheInterface = Cast<IDASelectable>(CurrentHighlight);
	if (TheInterface) {
		TheInterface->Execute_Highlight(CurrentHighlight);
	}
}
