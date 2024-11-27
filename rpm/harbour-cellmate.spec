Name:       harbour-cellmate

Summary:    Monitors the local cellular radio network
Version:    0.1
Release:    1
License:    GPL-3.0-or-later
URL:        https://github.com/james1465/harbour-cellmate
Source0:    %{name}-%{version}.tar.bz2
Requires:  qt5-qtdeclarative-import-sensors
Requires:  qt5-qtdeclarative-import-positioning
Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(sailfishapp) >= 1.0.2
BuildRequires:  pkgconfig(mlite5)
BuildRequires:  pkgconfig(qofono-qt5)
BuildRequires:  pkgconfig(qofonoext)
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  qt5-qtdeclarative-import-sensors
BuildRequires:  qt5-qtdeclarative-import-positioning
BuildRequires:  qt5-qtpositioning-devel
BuildRequires:  desktop-file-utils
BuildRequires:  qt5-qttools-linguist

%description
Monitors detected cells for LTE / UMTS and GSM. Reports these via the GUI and optionally records a logfile



%prep
# This description section includes metadata for SailfishOS:Chum, see
# https://github.com/sailfishos-chum/main/blob/main/Metadata.md
%if 0%{?_chum}
Title: CellMate
Type: desktop-application
DeveloperName: James
Categories:
 - Utilities
 - Science 
Custom:
  Repo: https://github.com/james1465/harbour-cellmate
PackageIcon: TODO
Screenshots:
 -  https://github.com/james1465/harbour-cellmate/blob/main/screenshots/serving_small.png
 -  https://github.com/james1465/harbour-cellmate/blob/main/screenshots/gsm_measurements_small.png
 -  https://github.com/james1465/harbour-cellmate/blob/main/screenshots/umts_measurements_small.png
 -  https://github.com/james1465/harbour-cellmate/blob/main/screenshots/lte_measurements_small.png
    TODO
Links:
  Homepage: https://github.com/james1465/harbour-cellmate
  Help: https://github.com/james1465/harbour-cellmate/discussions
  Bugtracker: https://github.com/james1465/harbour-cellmate/issues 
%endif

%setup -q -n %{name}-%{version}

%build

%qmake5 

%make_build


%install
%qmake5_install


desktop-file-install --delete-original         --dir %{buildroot}%{_datadir}/applications                %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png
