Name:       harbour-cellmate

Summary:    Monitors the local cellular radio network
Version:    0.1
Release:    1
License:    LICENSE
URL:        http://example.org/
Source0:    %{name}-%{version}.tar.bz2
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

%description
Monitors detected cells for LTE / UMTS and GSM. Reports these via the GUI and optionally records a logfile


%prep
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
