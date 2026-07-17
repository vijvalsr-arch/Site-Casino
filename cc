<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <title>Bank Dashboard</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500&display=swap" rel="stylesheet" />
  <style>
    :root {
      --bg: #000000;
      --card-bg: rgba(10, 10, 10, 0.8);
      --border: rgba(255, 255, 255, 0.14);
      --text-main: #ffffff;
      --text-muted: #b3b3b3;
      --accent-soft: rgba(255, 255, 255, 0.06);
      --shadow-soft: 0 24px 60px rgba(0, 0, 0, 0.9);
      --radius-card: 36px;
      --radius-pill: 999px;
      --transition-fast: 0.18s ease-out;
      --transition-med: 0.28s ease-out;
    }

    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
    }

    html, body {
      height: 100%;
      scroll-behavior: smooth;
    }

    body {
      font-family: "Inter", system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif;
      background: var(--bg);
      color: var(--text-main);
      display: flex;
      align-items: stretch;
      justify-content: center;
      padding: 32px 20px;
      position: relative;
      overflow-x: hidden;
    }

    /* Cinematic background beams */
    body::before,
    body::after {
      content: "";
      position: fixed;
      inset: -40%;
      background:
        linear-gradient(90deg, transparent 0%, rgba(255, 255, 255, 0.08) 50%, transparent 100%);
      opacity: 0.35;
      mix-blend-mode: screen;
      pointer-events: none;
      transform: translateX(-20%);
      animation: beams-move 26s linear infinite;
    }

    body::after {
      opacity: 0.18;
      filter: blur(18px);
      animation-duration: 38s;
      transform: translateX(20%);
    }

    @keyframes beams-move {
      0% { transform: translateX(-25%); }
      50% { transform: translateX(25%); }
      100% { transform: translateX(-25%); }
    }

    .glow-orbit {
      position: fixed;
      width: 520px;
      height: 520px;
      border-radius: 50%;
      background: radial-gradient(circle, rgba(255, 255, 255, 0.12) 0%, transparent 60%);
      filter: blur(40px);
      opacity: 0.35;
      pointer-events: none;
      top: 10%;
      left: 50%;
      transform: translateX(-50%);
    }

    .glow-orbit.secondary {
      width: 420px;
      height: 420px;
      top: auto;
      bottom: 5%;
      left: 18%;
      opacity: 0.22;
    }

    .glow-orbit.tertiary {
      width: 360px;
      height: 360px;
      bottom: 8%;
      right: 10%;
      opacity: 0.18;
    }

    .app-shell {
      position: relative;
      max-width: 1320px;
      width: 100%;
      z-index: 1;
      display: flex;
      flex-direction: column;
      gap: 24px;
    }

    /* Header */
    .app-header {
      display: grid;
      grid-template-columns: auto 1fr auto;
      align-items: center;
      gap: 16px;
      padding: 12px 24px 4px;
    }

    .header-side {
      display: flex;
      align-items: center;
      gap: 10px;
    }

    .header-title-block {
      text-align: center;
    }

    .header-title {
      font-size: 24px;
      font-weight: 500;
      letter-spacing: 0.02em;
    }

    .header-subtitle {
      font-size: 13px;
      font-weight: 300;
      color: var(--text-muted);
      margin-top: 4px;
    }

    .icon-button {
      border-radius: var(--radius-pill);
      border: 1px solid var(--border);
      background: rgba(255, 255, 255, 0.02);
      color: var(--text-main);
      padding: 8px 16px;
      font-size: 13px;
      font-weight: 400;
      display: inline-flex;
      align-items: center;
      gap: 8px;
      cursor: pointer;
      backdrop-filter: blur(18px);
      box-shadow: 0 0 0 rgba(255, 255, 255, 0);
      transition: transform var(--transition-fast), box-shadow var(--transition-med), background var(--transition-fast), border-color var(--transition-fast);
    }

    .icon-button span.icon {
      font-size: 14px;
      opacity: 0.8;
    }

    .icon-button:hover {
      transform: translateY(-1px);
      background: rgba(255, 255, 255, 0.06);
      border-color: rgba(255, 255, 255, 0.3);
      box-shadow: 0 0 18px rgba(255, 255, 255, 0.12);
    }

    .icon-button:active {
      transform: translateY(0);
      box-shadow: 0 0 0 rgba(255, 255, 255, 0.08);
      background: rgba(255, 255, 255, 0.03);
    }

    /* Layout */
    .app-main {
      display: grid;
      grid-template-columns: minmax(0, 1.2fr) minmax(0, 1fr);
      gap: 32px;
      align-items: flex-start;
    }

    @media (max-width: 1024px) {
      body {
        padding: 20px 14px;
      }
      .app-main {
        grid-template-columns: 1fr;
      }
    }

    @media (max-width: 720px) {
      .app-header {
        grid-template-columns: 1fr;
        justify-items: center;
      }
      .header-side {
        justify-content: center;
      }
    }

    /* Cards */
    .card {
      position: relative;
      border-radius: var(--radius-card);
      background: var(--card-bg);
      border: 1px solid var(--border);
      box-shadow: var(--shadow-soft), 0 0 0 1px rgba(255, 255, 255, 0.02);
      backdrop-filter: blur(26px);
      padding: 22px 24px;
      overflow: hidden;
      transition: transform var(--transition-med), box-shadow var(--transition-med), border-color var(--transition-med), background var(--transition-med), opacity 0.4s ease-out;
      opacity: 0;
      transform: translateY(12px);
    }

    .card::before {
      content: "";
      position: absolute;
      inset: -40%;
      background:
        radial-gradient(circle at 0% 0%, rgba(255, 255, 255, 0.12) 0%, transparent 55%),
        radial-gradient(circle at 100% 100%, rgba(255, 255, 255, 0.08) 0%, transparent 55%);
      opacity: 0.18;
      mix-blend-mode: screen;
      pointer-events: none;
    }

    .card:hover {
      transform: translateY(-4px);
      box-shadow: 0 26px 80px rgba(0, 0, 0, 0.95), 0 0 22px rgba(255, 255, 255, 0.16);
      border-color: rgba(255, 255, 255, 0.26);
      background: rgba(12, 12, 12, 0.9);
    }

    .card-header {
      display: flex;
      align-items: center;
      justify-content: space-between;
      margin-bottom: 18px;
    }

    .card-title {
      font-size: 17px;
      font-weight: 500;
      letter-spacing: 0.02em;
    }

    .card-subtitle {
      font-size: 13px;
      font-weight: 300;
      color: var(--text-muted);
      margin-top: 4px;
    }

    .card-tag {
      font-size: 11px;
      font-weight: 400;
      padding: 6px 12px;
      border-radius: var(--radius-pill);
      border: 1px solid rgba(255, 255, 255, 0.16);
      background: rgba(255, 255, 255, 0.02);
      color: var(--text-muted);
      backdrop-filter: blur(18px);
    }

    .card-body {
      display: flex;
      flex-direction: column;
      gap: 16px;
    }

    .card.visible {
      opacity: 1;
      transform: translateY(0);
    }

    /* Frame with buttons */
    .frame-card {
      padding: 26px 26px;
    }

    .frame-tabs {
      display: flex;
      flex-wrap: wrap;
      gap: 10px;
      margin-bottom: 18px;
    }

    .frame-tab-button {
      border-radius: var(--radius-pill);
      border: 1px solid rgba(255, 255, 255, 0.18);
      background: rgba(255, 255, 255, 0.02);
      color: var(--text-main);
      padding: 8px 16px;
      font-size: 13px;
      font-weight: 400;
      cursor: pointer;
      backdrop-filter: blur(18px);
      display: inline-flex;
      align-items: center;
      gap: 8px;
      transition: background var(--transition-fast), border-color var(--transition-fast), transform var(--transition-fast), box-shadow var(--transition-med);
    }

    .frame-tab-button.active {
      background: rgba(255, 255, 255, 0.12);
      border-color: rgba(255, 255, 255, 0.5);
      box-shadow: 0 16px 40px rgba(0, 0, 0, 0.9), 0 0 18px rgba(255, 255, 255, 0.16);
    }

    .frame-tab-button:hover {
      transform: translateY(-1px);
      background: rgba(255, 255, 255, 0.08);
      border-color: rgba(255, 255, 255, 0.4);
    }

    .frame-content {
      border-radius: 28px;
      border: 1px solid rgba(255, 255, 255, 0.18);
      background: rgba(255, 255, 255, 0.02);
      padding: 18px 18px 16px;
      backdrop-filter: blur(22px);
      min-height: 220px;
      display: none;
    }

    .frame-content.active {
      display: block;
    }

    .frame-section-title {
      font-size: 16px;
      font-weight: 500;
      margin-bottom: 6px;
    }

    .frame-section-subtitle {
      font-size: 13px;
      font-weight: 300;
      color: var(--text-muted);
      margin-bottom: 12px;
    }

    .frame-row {
      display: flex;
      justify-content: space-between;
      align-items: center;
      gap: 12px;
      margin-top: 10px;
    }

    .frame-stat-grid {
      display: grid;
      grid-template-columns: repeat(3, minmax(0, 1fr));
      gap: 12px;
      margin-top: 10px;
    }

    @media (max-width: 720px) {
      .frame-stat-grid {
        grid-template-columns: repeat(2, minmax(0, 1fr));
      }
    }

    .frame-stat-item {
      border-radius: 18px;
      border: 1px solid rgba(255, 255, 255, 0.12);
      background: rgba(255, 255, 255, 0.02);
      padding: 10px 12px;
      display: flex;
      flex-direction: column;
      gap: 4px;
      backdrop-filter: blur(18px);
      font-size: 12px;
    }

    .frame-stat-label {
      font-size: 11px;
      font-weight: 300;
      color: var(--text-muted);
    }

    .frame-stat-value {
      font-size: 14px;
      font-weight: 500;
      letter-spacing: 0.03em;
    }

    .frame-meta {
      display: flex;
      flex-direction: column;
      gap: 8px;
      font-size: 12px;
      color: var(--text-muted);
    }

    .frame-meta-row {
      display: flex;
      justify-content: space-between;
      align-items: center;
    }

    .frame-meta-label {
      font-weight: 300;
    }

    .frame-meta-value {
      font-weight: 400;
      color: #e0e0e0;
    }

    /* Balance details inside frame */
    .balance-main-label {
      font-size: 13px;
      font-weight: 300;
      color: var(--text-muted);
      margin-bottom: 6px;
    }

    .balance-main-value {
      font-size: 32px;
      font-weight: 500;
      letter-spacing: 0.04em;
      display: flex;
      align-items: baseline;
      gap: 10px;
    }

    .balance-main-value span.symbol {
      font-size: 20px;
      opacity: 0.8;
    }

    .balance-breakdown {
      display: flex;
      flex-wrap: wrap;
      gap: 16px;
      margin-top: 18px;
    }

    .balance-pill {
      border-radius: var(--radius-pill);
      border: 1px solid rgba(255, 255, 255, 0.18);
      background: rgba(255, 255, 255, 0.02);
      padding: 10px 14px;
      display: flex;
      align-items: center;
      justify-content: space-between;
      min-width: 160px;
      backdrop-filter: blur(18px);
    }

    .balance-pill-label {
      font-size: 12px;
      font-weight: 300;
      color: var(--text-muted);
    }

    .balance-pill-value {
      font-size: 16px;
      font-weight: 500;
      letter-spacing: 0.03em;
    }

    /* Buttons */
    .pill-button {
      border-radius: var(--radius-pill);
      border: 1px solid rgba(255, 255, 255, 0.18);
      background: #ffffff;
      color: #000000;
      padding: 10px 18px;
      font-size: 13px;
      font-weight: 500;
      letter-spacing: 0.02em;
      display: inline-flex;
      align-items: center;
      justify-content: center;
      gap: 8px;
      cursor: pointer;
      box-shadow: 0 12px 30px rgba(255, 255, 255, 0.12);
      position: relative;
      overflow: hidden;
      transition: transform var(--transition-fast), box-shadow var(--transition-med), background var(--transition-fast), color var(--transition-fast), border-color var(--transition-fast);
    }

    .pill-button::after
