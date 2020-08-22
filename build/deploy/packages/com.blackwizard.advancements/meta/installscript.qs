/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the FOO module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

function Component()
{
    var tempRepo = ["https://advancements.blackwizard.fr/repository/beta"]
    installer.setTemporaryRepositories(tempRepo, false)
    
    if (installer.isUpdater()) {
        var startMenuShortcut = installer.value("StartMenuDir") + "/Minecraft Advancements.lnk";
        var desktopShortcut = installer.value("DesktopDir") + "/Minecraft Advancements.lnk";
        if (installer.fileExists(startMenuShortcut)) {
            installer.setValue("shortcutStartMenuExistent", "oui")
        }

        if (installer.fileExists(desktopShortcut)) {
            installer.setValue("shortcutDesktopExistent", "oui")
        }
    }

    try {
        installer.addWizardPageItem(component, "StartMenuShortcutCheckBoxForm", QInstaller.StartMenuSelection);
    } catch(e) {
        console.log(e);
    }

    installer.installationFinished.connect(this, Component.prototype.installationFinishedPageIsShown);
    installer.finishButtonClicked.connect(this, Component.prototype.installationFinished);
}

Component.prototype.createOperations = function()
{

    component.createOperations();

    if (installer.isInstaller()) {
        var isStartMenuShortcutCheckBoxChecked = component.userInterface( "StartMenuShortcutCheckBoxForm" ).startMenuShortcutCheckBox.checked;
        var isDesktopShortcutCheckBoxChecked = component.userInterface( "StartMenuShortcutCheckBoxForm" ).desktopShortcutCheckBox.checked;
        if (isStartMenuShortcutCheckBoxChecked) {
            component.addOperation("CreateShortcut", "@TargetDir@/Minecraft-Advancements.exe", "@StartMenuDir@/Minecraft Advancements.lnk",
                "workingDirectory=@TargetDir@", "iconPath=@TargetDir@/Minecraft-Advancements.exe",
                "iconId=0", "description=Suivis Progrès Minecraft");

            component.addOperation("CreateShortcut", "@TargetDir@/maintenancetool.exe", "@StartMenuDir@/Minecraft Advancements Maintenance.lnk",
                "workingDirectory=@TargetDir@", "iconPath=@TargetDir@/maintenancetool.exe",
                "iconId=0", "description=Désinstaller ou mettre à jour Minecraft Advancements");
        }

        if (isDesktopShortcutCheckBoxChecked) {
            component.addOperation("CreateShortcut", "@TargetDir@/Minecraft-Advancements.exe", "@DesktopDir@/Minecraft Advancements.lnk",
                "workingDirectory=@TargetDir@", "iconPath=@TargetDir@/Minecraft-Advancements.exe",
                "iconId=0", "description=Suivis Progrès Minecraft");
        }

        component.addOperation("Execute", "{0,5100}", "@TargetDir@/bin/vcredist_x86_2010.exe", "/passive", "/norestart")
    }

    if (installer.isUpdater() && installer.value("shortcutStartMenuExistent") == "oui") {
        component.addOperation("CreateShortcut", "@TargetDir@/Minecraft-Advancements.exe", "@StartMenuDir@/Minecraft Advancements.lnk",
            "workingDirectory=@TargetDir@", "iconPath=@TargetDir@/Minecraft-Advancements.exe",
            "iconId=0", "description=Suivis Progrès Minecraft");

        component.addOperation("CreateShortcut", "@TargetDir@/maintenancetool.exe", "@StartMenuDir@/Minecraft Advancements Maintenance.lnk",
            "workingDirectory=@TargetDir@", "iconPath=@TargetDir@/maintenancetool.exe",
            "iconId=0", "description=Désinstaller ou mettre à jour Minecraft Advancements");
    }

    if (installer.isUpdater() && installer.value("shortcutDesktopExistent") == "oui") {
        component.addOperation("CreateShortcut", "@TargetDir@/Minecraft-Advancements.exe", "@DesktopDir@/Minecraft Advancements.lnk",
            "workingDirectory=@TargetDir@", "iconPath=@TargetDir@/Minecraft-Advancements.exe",
            "iconId=0", "description=Suivis Progrès Minecraft");
    }

    if (installer.isUpdater()) {
        component.addOperation("Execute", "{0,5100}", "@TargetDir@/bin/vcredist_x86_2010.exe", "/norestart", "/q")
    }
}

Component.prototype.installationFinishedPageIsShown = function()
{
    try {
        if (installer.status == QInstaller.Success) {
            installer.addWizardPageItem(component, "LaunchAtTheEnd", QInstaller.InstallationFinished);
        }
    } catch(e) {
        console.log(e);
    }
}

Component.prototype.installationFinished = function()
{
    try {
        if (installer.status == QInstaller.Success) {
            var isReadMeCheckBoxChecked = component.userInterface( "LaunchAtTheEnd" ).launchCheckBox.checked;
            if (isReadMeCheckBoxChecked) {
                QDesktopServices.openUrl("file:///" + installer.value("TargetDir") + "/Minecraft-Advancements.exe");
            }
        }
    } catch(e) {
        console.log(e);
    }
}
