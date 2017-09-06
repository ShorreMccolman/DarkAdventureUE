// Fill out your copyright notice in the Description page of Project Settings.

#include "DAWidget.h"
#include "DAButton.h"
#include "WidgetNavigation.h"

void UDAWidget::Accept()
{
	if (HighlightedButton) {
		HighlightedButton->OnClicked.Broadcast();
	}
}

void UDAWidget::Cancel()
{

}

void UDAWidget::OnOpen()
{
	SetHighlightedButton(DefaultSelection);
}

void UDAWidget::OnClose()
{

}

void UDAWidget::NavigateUp()
{
	if (HighlightedButton) {
		UWidgetNavigation* Nav = HighlightedButton->Navigation;
		if (Nav) {
			UDAButton *Button = Cast<UDAButton>(Nav->Up.Widget.Get());
			if (Button) {
				SetHighlightedButton(Button);
			}
		}
	}
}

void UDAWidget::NavigateRight()
{
	if (HighlightedButton) {
		UWidgetNavigation* Nav = HighlightedButton->Navigation;
		if (Nav) {
			UDAButton *Button = Cast<UDAButton>(Nav->Right.Widget.Get());
			if (Button) {
				SetHighlightedButton(Button);
			}
		}
	}
}

void UDAWidget::NavigateDown()
{
	if (HighlightedButton) {
		UWidgetNavigation* Nav = HighlightedButton->Navigation;
		if (Nav) {
			UDAButton *Button = Cast<UDAButton>(Nav->Down.Widget.Get());
			if (Button) {
				SetHighlightedButton(Button);
			}
		}
	}
}

void UDAWidget::NavigateLeft()
{
	if (HighlightedButton) {
		UWidgetNavigation* Nav = HighlightedButton->Navigation;
		if (Nav) {
			UDAButton *Button = Cast<UDAButton>(Nav->Left.Widget.Get());
			if (Button) {
				SetHighlightedButton(Button);
			}
		}
	}
}

void UDAWidget::SetHighlightedButton(UDAButton* Button)
{
	if (HighlightedButton) {
		HighlightedButton->SetBackgroundColor(FLinearColor::White);
	}

	HighlightedButton = Button;
	HighlightedButton->SetBackgroundColor(FLinearColor::Blue);
}
